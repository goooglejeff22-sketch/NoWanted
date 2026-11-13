// No Wanted Level - AML (Android Mod Loader) mod for GTA SA (arm64-v8a)
// Needs the AML headers (the "mod/" folder) from https://github.com/RusJJ/AndroidModLoader
#include <mod/amlmod.h>
#include <mod/logger.h>

MYMODCFG(net.example.nowanted, No Wanted Level, 1.0.0, YourName)
NEEDGAME(com.rockstargames.gtasa)

uintptr_t pGTASA = 0;
void*     hGTASA = nullptr;

// CWanted::SetWantedLevel(int)
DECL_HOOKv(SetWantedLevel, void* self, int level)
{
    SetWantedLevel(self, 0); // call original, always with level 0
}

// CWanted::SetWantedLevelNoDrop(int)
DECL_HOOKv(SetWantedLevelNoDrop, void* self, int level)
{
    SetWantedLevelNoDrop(self, 0);
}

extern "C" void OnModLoad()
{
    logger->SetTag("NoWanted");

    pGTASA = aml->GetLib("libGTASA.so");
    hGTASA = aml->GetLibHandle("libGTASA.so");
    if (!pGTASA || !hGTASA)
    {
        logger->Error("libGTASA.so not found");
        return;
    }

    void* fnSet    = aml->GetSym(hGTASA, "_ZN7CWanted14SetWantedLevelEi");
    void* fnNoDrop = aml->GetSym(hGTASA, "_ZN7CWanted20SetWantedLevelNoDropEi");

    if (fnSet)    HOOK(SetWantedLevel, fnSet);
    else          logger->Error("SetWantedLevel symbol not found");

    if (fnNoDrop) HOOK(SetWantedLevelNoDrop, fnNoDrop);
    else          logger->Error("SetWantedLevelNoDrop symbol not found");

    logger->Info("Loaded");
}
