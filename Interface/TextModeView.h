#ifndef NSAPPLICATION_NSINTERFACE_CTEXTMODEVIEW_H
#define NSAPPLICATION_NSINTERFACE_CTEXTMODEVIEW_H

#include <QObject>

#include <memory>

#include "Kernel/TextMode.h"
#include "Library/Observer/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Library/StlExtension/Supressor.h"
#include "Local/Localizer.h"

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QGroupBox;
class QRadioButton;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSTextModeViewDetail {

class CTextModeViewImpl : public QObject {
  Q_OBJECT

  using ETextMode = NSKernel::ETextMode;
  using EModifierMode = NSKernel::EModifierMode;

  using CTextMode = NSKernel::CTextMode;
  using CTextModeObserver = NSLibrary::CObserver<CTextMode>;
  using CTextModeInput = NSLibrary::CHotInput<CTextMode>;

  using CETextModeObserver = NSLibrary::CObserver<ETextMode>;
  using CETextModeObservable = NSLibrary::CObservableData<ETextMode>;

  using CLocalizer = NSLocal::CTextModeViewLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

  using CSupressor = NSLibrary::CSupressor;

public:
  struct CInitData {
    QButtonGroup* TextModeGroup;
    QGroupBox* TextModeBox;
    QRadioButton* Raw;
    QRadioButton* Full;
    QRadioButton* Printed;
  };

  CTextModeViewImpl(const CInitData& InitData);

  CTextModeObserver* textModeInput();
  CLocalizerObserver* localizerInput();
  void subscribeToTextMode(CETextModeObserver*);

public Q_SLOTS:
  void TextButtonToggled(int id, bool checked);
  void handleTextModeSwitchByGui();

  void toggleTextButton(int id);

  void toggleAllButtons(CTextMode);

private:
  static ETextMode getTextMode(int);
  static EModifierMode getModifierMod(int);
  static int getTextInt(ETextMode);
  static int getModifierInt(EModifierMode);

  void onTextModeInput(const CTextMode& Mode);
  ETextMode getCurrentTextMode() const;
  bool areSwitchesInCorrectState() const;
  void setLocale(const CLocalizer& Localizer);

  QButtonGroup* TextModeGroup_;
  QGroupBox* TextModeBox_;
  QRadioButton* Raw_;
  QRadioButton* Full_;
  QRadioButton* Printed_;

  CSupressor FromModel_;
  CSupressor MySignal_;

  CTextModeInput TextModeInput_;
  CETextModeObservable TextModeOutput_;
  CLocalizerInput LocalizerInput_;
};
} // namespace NSTextModeViewDetail

class CTextModeView
    : public NSLibrary::CViewWrapper<NSTextModeViewDetail::CTextModeViewImpl> {
  using CTextModeViewImpl = NSTextModeViewDetail::CTextModeViewImpl;
  using CBase = NSLibrary::CViewWrapper<CTextModeViewImpl>;

public:
  using CInitData = CTextModeViewImpl::CInitData;

  using CBase::CBase;
};
} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CTEXTMODEVIEW_H
