#ifndef NSAPPLICATION_CAPPLICATIONKERNEL_H
#define NSAPPLICATION_CAPPLICATIONKERNEL_H

#include "ApplicationGlobals.h"
#include "Kernel/AnalyticalModule.h"
#include "Kernel/KeySchemeModule.h"
#include "Kernel/SeanceManager.h"
#include "Kernel/SessionSelector.h"
#include "Kernel/StatisticsModule.h"
#include "Kernel/TextModule.h"
#include "Kernel/UserDataModule.h"
#include "Local/LocalizationModule.h"

namespace NSApplication {

class CApplicationKernel : protected CApplicationGlobals {
  using CSeanceManager = NSKernel::CSeanceManager;
  using CSessionSelector = NSKernel::CSessionSelector;
  using CTextModule = NSKernel::CTextModule;
  using CAnalyticalModule = NSKernel::CAnalyticalModule;
  using CUserDataModule = NSKernel::CUserDataModule;
  using CKeySchemeModule = NSKernel::CKeySchemeModule;
  using CStatisticsModule = NSKernel::CStatisticsModule;
  using CLocalizationModule = NSLocal::CLocalizationModule;

public:
  CApplicationKernel();

protected:
  CSeanceManager SeanceManager_;
  CSessionSelector SessionSelector_;
  CTextModule TextModule_;
  CAnalyticalModule AnalyticalModule_;
  CUserDataModule UserData_;
  CKeySchemeModule KeySchemeModule_;
  CStatisticsModule StatisticsModule_;
  CLocalizationModule LocalizationModule_;
};

} // namespace NSApplication

#endif // NSAPPLICATION_CAPPLICATIONKERNEL_H
