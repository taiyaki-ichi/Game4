#include"Sound.hpp"
#include"Window.hpp"
#include<Windows.h>
#include<iostream>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
// mmioで必要
#pragma comment(lib, "winmm.lib")

namespace GameLib
{
	static LPDIRECTSOUND8 g_SoundInterface = nullptr;

	struct WavData
	{
		WAVEFORMATEX WavFormat;
		char* SoundBuffer;
		DWORD Size;
	};

	bool LoadWavFile(const std::string& fileName, WavData* data);

	SoundManager::SoundManager()
	{
	}

	SoundManager::~SoundManager()
	{
		if (g_SoundInterface)
			g_SoundInterface->Release();
	}

	bool SoundManager::Init()
	{
		// DirectSoundの生成
		if (FAILED(DirectSoundCreate8(
			NULL,				// GUID
			&g_SoundInterface,	// 生成したDirectSound保存先
			NULL)))				// NULL固定
		{
			std::cout << "DirectSoundCreate8 is failed\n";
			return false;
		}

		// 協調レベルの設定
		if (FAILED(g_SoundInterface->SetCooperativeLevel(
			FindWindow(WINDOW_CLASS_NAME, nullptr),		// ウィンドウハンドル
			DSSCL_NORMAL)))								// 協調レベル
		{
			std::cout << "SetCooperativeLevel is failed\n";
			return false;
		}

		return true;
	}



	Sound::Sound(LPDIRECTSOUNDBUFFER ptr)
		:mPtr(ptr)
	{
	}

	Sound::~Sound()
	{
		if (mPtr)
			mPtr->Release();
	}

	Sound* LoadSound(const std::string& fileName)
	{
		LPDIRECTSOUNDBUFFER buffPtr;
		WavData wavData;

		if (LoadWavFile(fileName, &wavData) == false)
		{
			std::cout << "LoadWavFile is failed\n";
			return nullptr;
		}

		// バッファ情報の設定
		DSBUFFERDESC dsbd;
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
		dsbd.dwBufferBytes = wavData.Size;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wavData.WavFormat;

		// セカンダリバッファ作成
		if (FAILED(g_SoundInterface->CreateSoundBuffer(
			&dsbd,					// バッファ情報
			&buffPtr,				// 作成されたバッファの保存先
			NULL)))
		{
			// 作成失敗
			std::cout << "CreateSoundBuffer is failed\n";
			delete[] wavData.SoundBuffer;
			return nullptr;
		}

		// 波形データを書き込むためにセカンダリバッファをロックする
		void* buffer;
		DWORD buffer_size;
		if (FAILED(buffPtr->Lock(
			0,				// オフセット
			wavData.Size,	// ロックするバッファサイズ
			&buffer,		// ロックされたバッファパート１の保存先
			&buffer_size,	// ロックされたバッファパート１のサイズ
			NULL,			// ロックされたバッファパート２の保存先
			NULL,			// ロックされたバッファパート２のサイズ
			0)))			// ロックオプション
		{
			// ロック失敗
			std::cout << "buffer Lock is failed\n";
			delete[] wavData.SoundBuffer;
			return nullptr;
		}

		memcpy(buffer, wavData.SoundBuffer, buffer_size);

		buffPtr->Unlock(
			&buffer,		// アンロックするバッファパート１
			buffer_size,	// パート１のバッファサイズ
			NULL,			// アンロックするバッファパート２
			NULL);			// パート２のバッファサイズ

		// コピーが終わったのでサウンドデータを解放
		delete[] wavData.SoundBuffer;

		if (buffPtr)
			return new Sound(buffPtr);
		else
			return nullptr;
	}

	Sound* CopySoundData(Sound* sound)
	{
		LPDIRECTSOUNDBUFFER newBuffPtr;
		if (FAILED(g_SoundInterface->DuplicateSoundBuffer(
			sound->GetPtr(), &newBuffPtr)))
		{
			return nullptr;
		}

		return new Sound(newBuffPtr);
	}

	void SoundPlay(Sound* sound, bool loop)
	{
		sound->GetPtr()->SetCurrentPosition(0);
		if (loop)
			sound->GetPtr()->Play(0, 0, DSBPLAY_LOOPING);
		else
			sound->GetPtr()->Play(0, 0, 0);
	}

	void SoundStop(Sound* sound)
	{
		sound->GetPtr()->Stop();
	}

	void SetSoundVolume(Sound* sound, unsigned int vol)
	{
		long v = (DSBVOLUME_MAX - DSBVOLUME_MIN) * vol / 100.f + DSBVOLUME_MIN;
		sound->GetPtr()->SetVolume(v);
	}


	bool LoadWavFile(const std::string& fileName, WavData* data)
	{
		// WindowsマルチメディアAPIのハンドル
		HMMIO mmio_handle = NULL;

		// チャンク情報
		MMCKINFO ck_info;
		// RIFFチャンク用
		MMCKINFO riffck_info;

		// WAVファイル内音サンプルのサイズ
		DWORD dwWavSize = 0;

		// WAVファイルを開く
		mmio_handle = mmioOpen(
			(char*)fileName.c_str(),	// ファイル名
			NULL,				// MMIO情報
			MMIO_READ);			// オープンモード

		if (mmio_handle == NULL)
		{
			// オープン失敗
			return false;
		}

		// RIFFチャンクに進入するためにfccTypeにWAVEを設定する
		riffck_info.fccType = mmioFOURCC('W', 'A', 'V', 'E');

		// RIFFチャンクに侵入する
		if (MMSYSERR_NOERROR != mmioDescend(
			mmio_handle,	// MMIOハンドル
			&riffck_info,	// 取得したチャンクの情報
			NULL,			// 親チャンク
			MMIO_FINDRIFF))	// 取得情報の種類
		{
			// 失敗
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// 進入先のチャンクを"fmt "として設定する
		ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
		if (MMSYSERR_NOERROR != mmioDescend(mmio_handle, &ck_info, &riffck_info, MMIO_FINDCHUNK))
		{
			// fmtチャンクがない
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// fmtデータの読み込み
		LONG read_size = mmioRead(
			mmio_handle,						// ハンドル
			(HPSTR)&data->WavFormat,	// 読み込み用バッファ
			sizeof(data->WavFormat));	// バッファサイズ

		if (read_size != sizeof(data->WavFormat))
		{
			// 読み込みサイズが一致してないのでエラー
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// フォーマットチェック
		if (data->WavFormat.wFormatTag != WAVE_FORMAT_PCM)
		{
			// フォーマットエラー
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// fmtチャンクを退出する
		if (mmioAscend(mmio_handle, &ck_info, 0) != MMSYSERR_NOERROR)
		{
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// dataチャンクに進入する
		ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
		if (mmioDescend(mmio_handle, &ck_info, &riffck_info, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		{
			// 進入失敗
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// サイズを保存
		data->Size = ck_info.cksize;

		// dataチャンク読み込み
		data->SoundBuffer = new char[ck_info.cksize];
		read_size = mmioRead(mmio_handle, (HPSTR)data->SoundBuffer, ck_info.cksize);
		if (read_size != ck_info.cksize)
		{
			mmioClose(mmio_handle, MMIO_FHOPEN);
			delete[] data->SoundBuffer;
			return false;
		}

		// ファイルを閉じる
		mmioClose(mmio_handle, MMIO_FHOPEN);

		return true;
	}
}