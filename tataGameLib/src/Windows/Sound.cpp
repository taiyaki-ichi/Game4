#include"Sound.hpp"
#include"Window.hpp"
#include<Windows.h>
#include<iostream>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
// mmio�ŕK�v
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
		// DirectSound�̐���
		if (FAILED(DirectSoundCreate8(
			NULL,				// GUID
			&g_SoundInterface,	// ��������DirectSound�ۑ���
			NULL)))				// NULL�Œ�
		{
			std::cout << "DirectSoundCreate8 is failed\n";
			return false;
		}

		// �������x���̐ݒ�
		if (FAILED(g_SoundInterface->SetCooperativeLevel(
			FindWindow(WINDOW_CLASS_NAME, nullptr),		// �E�B���h�E�n���h��
			DSSCL_NORMAL)))								// �������x��
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

		// �o�b�t�@���̐ݒ�
		DSBUFFERDESC dsbd;
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
		dsbd.dwBufferBytes = wavData.Size;
		dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
		dsbd.lpwfxFormat = &wavData.WavFormat;

		// �Z�J���_���o�b�t�@�쐬
		if (FAILED(g_SoundInterface->CreateSoundBuffer(
			&dsbd,					// �o�b�t�@���
			&buffPtr,				// �쐬���ꂽ�o�b�t�@�̕ۑ���
			NULL)))
		{
			// �쐬���s
			std::cout << "CreateSoundBuffer is failed\n";
			delete[] wavData.SoundBuffer;
			return nullptr;
		}

		// �g�`�f�[�^���������ނ��߂ɃZ�J���_���o�b�t�@�����b�N����
		void* buffer;
		DWORD buffer_size;
		if (FAILED(buffPtr->Lock(
			0,				// �I�t�Z�b�g
			wavData.Size,	// ���b�N����o�b�t�@�T�C�Y
			&buffer,		// ���b�N���ꂽ�o�b�t�@�p�[�g�P�̕ۑ���
			&buffer_size,	// ���b�N���ꂽ�o�b�t�@�p�[�g�P�̃T�C�Y
			NULL,			// ���b�N���ꂽ�o�b�t�@�p�[�g�Q�̕ۑ���
			NULL,			// ���b�N���ꂽ�o�b�t�@�p�[�g�Q�̃T�C�Y
			0)))			// ���b�N�I�v�V����
		{
			// ���b�N���s
			std::cout << "buffer Lock is failed\n";
			delete[] wavData.SoundBuffer;
			return nullptr;
		}

		memcpy(buffer, wavData.SoundBuffer, buffer_size);

		buffPtr->Unlock(
			&buffer,		// �A�����b�N����o�b�t�@�p�[�g�P
			buffer_size,	// �p�[�g�P�̃o�b�t�@�T�C�Y
			NULL,			// �A�����b�N����o�b�t�@�p�[�g�Q
			NULL);			// �p�[�g�Q�̃o�b�t�@�T�C�Y

		// �R�s�[���I������̂ŃT�E���h�f�[�^�����
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
		// Windows�}���`���f�B�AAPI�̃n���h��
		HMMIO mmio_handle = NULL;

		// �`�����N���
		MMCKINFO ck_info;
		// RIFF�`�����N�p
		MMCKINFO riffck_info;

		// WAV�t�@�C�������T���v���̃T�C�Y
		DWORD dwWavSize = 0;

		// WAV�t�@�C�����J��
		mmio_handle = mmioOpen(
			(char*)fileName.c_str(),	// �t�@�C����
			NULL,				// MMIO���
			MMIO_READ);			// �I�[�v�����[�h

		if (mmio_handle == NULL)
		{
			// �I�[�v�����s
			return false;
		}

		// RIFF�`�����N�ɐi�����邽�߂�fccType��WAVE��ݒ肷��
		riffck_info.fccType = mmioFOURCC('W', 'A', 'V', 'E');

		// RIFF�`�����N�ɐN������
		if (MMSYSERR_NOERROR != mmioDescend(
			mmio_handle,	// MMIO�n���h��
			&riffck_info,	// �擾�����`�����N�̏��
			NULL,			// �e�`�����N
			MMIO_FINDRIFF))	// �擾���̎��
		{
			// ���s
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// �i����̃`�����N��"fmt "�Ƃ��Đݒ肷��
		ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
		if (MMSYSERR_NOERROR != mmioDescend(mmio_handle, &ck_info, &riffck_info, MMIO_FINDCHUNK))
		{
			// fmt�`�����N���Ȃ�
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// fmt�f�[�^�̓ǂݍ���
		LONG read_size = mmioRead(
			mmio_handle,						// �n���h��
			(HPSTR)&data->WavFormat,	// �ǂݍ��ݗp�o�b�t�@
			sizeof(data->WavFormat));	// �o�b�t�@�T�C�Y

		if (read_size != sizeof(data->WavFormat))
		{
			// �ǂݍ��݃T�C�Y����v���ĂȂ��̂ŃG���[
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// �t�H�[�}�b�g�`�F�b�N
		if (data->WavFormat.wFormatTag != WAVE_FORMAT_PCM)
		{
			// �t�H�[�}�b�g�G���[
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// fmt�`�����N��ޏo����
		if (mmioAscend(mmio_handle, &ck_info, 0) != MMSYSERR_NOERROR)
		{
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// data�`�����N�ɐi������
		ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
		if (mmioDescend(mmio_handle, &ck_info, &riffck_info, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		{
			// �i�����s
			mmioClose(mmio_handle, MMIO_FHOPEN);
			return false;
		}

		// �T�C�Y��ۑ�
		data->Size = ck_info.cksize;

		// data�`�����N�ǂݍ���
		data->SoundBuffer = new char[ck_info.cksize];
		read_size = mmioRead(mmio_handle, (HPSTR)data->SoundBuffer, ck_info.cksize);
		if (read_size != ck_info.cksize)
		{
			mmioClose(mmio_handle, MMIO_FHOPEN);
			delete[] data->SoundBuffer;
			return false;
		}

		// �t�@�C�������
		mmioClose(mmio_handle, MMIO_FHOPEN);

		return true;
	}
}