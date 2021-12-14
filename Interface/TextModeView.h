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
  using CTextModeObservable = NSLibrary::CObservableData<CTextMode>;

  using CTextModeViewLocalizer = NSLocal::CTextModeViewLocalizer;
  using CTextModeViewLocalizerObserver =
      NSLibrary::CObserver<CTextModeViewLocalizer>;
  using CTextModeViewLocalizerInput =
      NSLibrary::CHotInput<CTextModeViewLocalizer>;

  using CSupressor = NSLibrary::CSupressor;

public:
  struct CInitData {
    QButtonGroup* TextModeGroup;
    QGroupBox* TextModeBox;
    QRadioButton* Raw;
    QRadioButton* Full;
    QRadioButton* Printed;
    QButtonGroup* ShiftGroup;
    QGroupBox* ShiftBox;
    QRadioButton* ShiftNon;
    QRadioButton* ShiftAll;
    QRadioButton* ShiftEssential;
    QButtonGroup* CtrlGroup;
    QGroupBox* CtrlBox;
    QRadioButton* CtrlNon;
    QRadioButton* CtrlAll;
    QRadioButton* CtrlEssential;
    QButtonGroup* AltGroup;
    QGroupBox* AltBox;
    QRadioButton* AltNon;
    QRadioButton* AltAll;
    QRadioButton* AltEssential;
  };

  CTextModeViewImpl(const CInitData& InitData);

  CTextModeObserver* textModeInput();
  CTextModeViewLocalizerObserver* textModeViewLocalizerInput();
  void subscribeToTextMode(CTextModeObserver*);

public Q_SLOTS:
  void TextButtonToggled(int id, bool checked);
  void ShiftButtonToggled(int id, bool checked);
  void CtrlButtonToggled(int id, bool checked);
  void AltButtonToggled(int id, bool checked);
  void handleTextModeSwitchByGui();

  void toggleTextButton(int id);
  void toggleShiftButton(int id);
  void toggleCtrlButton(int id);
  void toggleAltButton(int id);

  void toggleAllButtons(CTextMode);

private:
  static ETextMode getTextMode(int);
  static EModifierMode getModifierMod(int);
  static int getTextInt(ETextMode);
  static int getModifierInt(EModifierMode);

  void onTextModeInput(const CTextMode& Mode);
  CTextMode getCurrentTextMode() const;
  bool areSwitchesInCorrectState() const;
  void setLocale(const CTextModeViewLocalizer& Localizer);

  QButtonGroup* TextModeGroup_;
  QGroupBox* TextModeBox_;
  QRadioButton* Raw_;
  QRadioButton* Full_;
  QRadioButton* Printed_;

  QButtonGroup* ShiftGroup_;
  QGroupBox* ShiftBox_;
  QRadioButton* ShiftNon_;
  QRadioButton* ShiftAll_;
  QRadioButton* ShiftEssential_;

  QButtonGroup* CtrlGroup_;
  QGroupBox* CtrlBox_;
  QRadioButton* CtrlNon_;
  QRadioButton* CtrlAll_;
  QRadioButton* CtrlEssential_;

  QButtonGroup* AltGroup_;
  QGroupBox* AltBox_;
  QRadioButton* AltNon_;
  QRadioButton* AltAll_;
  QRadioButton* AltEssential_;

  CSupressor FromModel_;
  CSupressor MySignal_;

  CTextModeInput TextModeInput_;
  CTextModeObservable TextModeOutput_;
  CTextModeViewLocalizerInput TextModeViewLocalizerInput_;
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
