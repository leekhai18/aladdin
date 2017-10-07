//-----------------------------------------------------------------------------
// File: DSUtil.h
//
// Desc: 
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
//
// Note: This file has been edited for use in Beginning Game Programming, Third Edition,
// originally distributed with a 2004 release of DirectX 9.0c SDK.
//

#ifndef DSUTIL_H
#define DSUTIL_H

#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// Classes used by this header
//-----------------------------------------------------------------------------
class CSoundManager;
class CSound;
class CStreamingSound;
class CWaveFile;




//-----------------------------------------------------------------------------
// Typing macros 
//-----------------------------------------------------------------------------
#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2

#define DSUtil_StopSound(s)         { if(s) s->Stop(); }
#define DSUtil_PlaySound(s)         { if(s) s->Play( 0, 0 ); }
#define DSUtil_PlaySoundLooping(s)  { if(s) s->Play( 0, DSBPLAY_LOOPING ); }




//-----------------------------------------------------------------------------
// Name: class CSoundManager
// Desc: 
//-----------------------------------------------------------------------------
class CSoundManager
{
protected:
  LPDIRECTSOUND8 m_pDS;

public:
  CSoundManager();
  ~CSoundManager();

  HRESULT Initialize(HWND hWnd, DWORD dwCoopLevel);
  inline  LPDIRECTSOUND8 GetDirectSound() { return m_pDS; }
  HRESULT SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate);

  HRESULT Create(CSound** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
};




//-----------------------------------------------------------------------------
// Name: class CSound
// Desc: Encapsulates functionality of a DirectSound buffer.
//-----------------------------------------------------------------------------
class CSound
{
protected:
  LPDIRECTSOUNDBUFFER* m_apDSBuffer;
  DWORD                m_dwDSBufferSize;
  CWaveFile*           m_pWaveFile;
  DWORD                m_dwNumBuffers;
  DWORD                m_dwCreationFlags;

  HRESULT RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored);

public:
  CSound(LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize, DWORD dwNumBuffers, CWaveFile* pWaveFile, DWORD dwCreationFlags);
  virtual ~CSound();

  HRESULT FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger);
  LPDIRECTSOUNDBUFFER GetFreeBuffer();

  HRESULT Play(DWORD dwPriority = 0, DWORD dwFlags = 0, LONG lVolume = 0, LONG lFrequency = -1, LONG lPan = 0);
  HRESULT Play(LONG lVolume);
  HRESULT Stop();
  HRESULT Reset();
  BOOL    IsSoundPlaying();
};


//-----------------------------------------------------------------------------
// Name: class CWaveFile
// Desc: Encapsulates reading or writing sound data to or from a wave file
//-----------------------------------------------------------------------------
class CWaveFile
{
public:
  WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
  HMMIO         m_hmmio;       // MM I/O handle for the WAVE
  MMCKINFO      m_ck;          // Multimedia RIFF chunk
  MMCKINFO      m_ckRiff;      // Use in opening a WAVE file
  DWORD         m_dwSize;      // The size of the wave file
  MMIOINFO      m_mmioinfoOut;
  DWORD         m_dwFlags;
  BOOL          m_bIsReadingFromMemory;
  BYTE*         m_pbData;
  BYTE*         m_pbDataCur;
  ULONG         m_ulDataSize;
  CHAR*         m_pResourceBuffer;

protected:
  HRESULT ReadMMIO();
  HRESULT WriteMMIO(WAVEFORMATEX *pwfxDest);

public:
  CWaveFile();
  ~CWaveFile();

  HRESULT Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags);
  HRESULT Close();

  HRESULT Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
  HRESULT Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote);

  DWORD   GetSize();
  HRESULT ResetFile();
  WAVEFORMATEX* GetFormat() { return m_pwfx; };
};




bool DirectSound_Init(HWND hwnd);
void DirectSound_Shutdown();
CSound *LoadSound(string filename);
void PlaySound(CSound *sound);
void LoopSound(CSound *sound);
void StopSound(CSound *sound);
void PlaySound(CSound *sound, LONG volume);
#endif // DSUTIL_H