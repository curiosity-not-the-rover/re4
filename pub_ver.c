#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <mmeapi.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>




HMODULE loaddll(char *dir) {

    HMODULE loadthis =  LoadLibrary(dir);
    if (loadthis == NULL) {
        printf("Error loading DLL: ");
        printf(dir);
        printf("\n");
    } else {
        printf("Amazing success! Loaded DLL: ");
        printf(dir);
        printf("\n");
    }
    return loadthis;
}
void exitdll(HMODULE h){
    FreeLibrary(h);
}

static char* phonemev[20][2] = {"V", "{", "Q", "i:", "I", "u:", "U", "e", "O:", "Q@", "@r", "aI", "aU", "I@", "U@", "eI", "OI", "O@", "@U"};

void audioloop() {
    timeGetTime();
}

int main() {
    printf("haihai! welcome welcome! starting audio service...\n");
    //HRESULT h2 = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    u_int devicesc = waveOutGetNumDevs();
    WAVEOUTCAPS devices[devicesc];
    for (u_int i = 0; i < devicesc; i++) {
        waveOutGetDevCapsA(i, &devices[i], 100);
    }

    //load dll files
    SetDllDirectory("C:/Program Files/VocaloidApi4/");
    HMODULE openvs4 = loaddll("OpenVS4.dll");
    HMODULE dft = loaddll("va_DSE4_DFT.dll");
    HMODULE dse4 = loaddll("va_DSE4.dll");
    HMODULE dbm = loaddll("va_DBM4.dll");
    //load functions from dlls
    
    FARPROC open4init = GetProcAddress(openvs4, "Initialize");
    FARPROC open4start = GetProcAddress(openvs4, "CreateOpenVS");
    FARPROC open4terminate = GetProcAddress(openvs4, "Terminate");
    FARPROC sing = GetProcAddress(dse4, "DoStepSynthesis");
    FARPROC dbm2 = GetProcAddress(dbm, "CreateDBM2");
    
    
    LPWSTR passcode = (LPWSTR)(L"Ђ[KEY_HERE_SEE_README]");
    printf("Now initializing VOCALOID4... This might take a second! Please be patient! (*/ω＼*)");
    u_int init = (u_int)(*open4init)(passcode);
    printf("%d\n", init);
    if (init == 0) {
        printf("Successfully Initialized! q(≧ ∀ ≦ q)\n");
    } else {
        printf("Failed to start! Check your input and try again please!\n");
    }
    u_int startresult = (u_int)(open4start)((void*)(L"襌⑌䰠䒉ᠤ襈⑔䠐䲉ࠤ荈⣬譌䧉킸ꩧ︗䠀º✀ﶎ䠀궹퇬"));
    printf("VOCALOID4 session started! ID: %d\n", startresult);
    //int voicebase = (int)(dbm2)();
    printf("I have a voice, and I must sing! Your move now (≧ ∀ ≦ )ゞ\n");
    printf("Please try typing below with vocaloid phonetics! p.s.: the manual should have come with your purchase (●'◡'●). For one-character phoenemes, please place a slash ('/') after the phoneme letter.\n");
    char phon[2];
    scanf("%c%c", &phon);
    //for (int i = 0; i < 1000000; i++) {
    //    audioloop();
    //}
    //end program
    void * term = (void*)(*open4terminate)();
    exitdll(dse4);
    exitdll(openvs4);
    exitdll(dft);
    exitdll(dbm);
    return 0;
}
