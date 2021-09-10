#include "SessionSelectorOut.h"
#include "Kernel/SessionSelector/SessionSelectorGUI.h"

#include <QObject>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

namespace NSApplication {
namespace NSInterface {

namespace NSSessionSelectorOutDetail {

CSessionSelectorOutImpl::CSessionSelectorOutImpl(CMainWindow* MainWindow)
    : ui_(std::make_unique<CSessionSelectorGUI>(MainWindow)),
      CurrentSeanceInput_(
          [this](const CSeance& Seance) { processCurrentSeance(Seance); }),
      SessionIndexOutput_([this]() -> int { return SessionIndex_; }) {
  setUpUI();
  connectUI();
}

CSessionSelectorOutImpl::~CSessionSelectorOutImpl() = default;

void CSessionSelectorOutImpl::subscribeToSessionIndex(
    CSessionIndexObserver* observer) {
  SessionIndexOutput_.subscribe(observer);
}

CSessionSelectorOutImpl::CSeanceObserver*
CSessionSelectorOutImpl::currentSeanceInput() {
  return &CurrentSeanceInput_;
}

void CSessionSelectorOutImpl::setUpUI() {
  if (CurrentSeanceInput_.isActive()) {
    outputCurrentSeance(CurrentSeance_.value());
  } else {
    setUpNoSeanceCase();
  }
}

void CSessionSelectorOutImpl::connectUI() {
  QObject::connect(ui_->SelectButton(), &QPushButton::clicked, this,
                   &CSessionSelectorOutImpl::updateSessionIndex);
  QObject::connect(ui_->ResetButton(), &QPushButton::clicked, this,
                   &CSessionSelectorOutImpl::resetSessionIndex);
}

void CSessionSelectorOutImpl::processCurrentSeance(const CSeance& Seance) {
  CurrentSeance_ = Seance;
  setUpUI();
}

void CSessionSelectorOutImpl::outputCurrentSeance(const CSeance& Seance) {
  ui_->Text()->setText(getSeanceDescription(Seance));
  if (Seance.size() > 0) {
    setUpRegularCase(Seance);
  } else {
    setUpEmptyCase();
  }
}

void CSessionSelectorOutImpl::setUpRegularCase(const CSeance& Seance) {
  ui_->SelectionMenu()->setRange(1, Seance.size());
  ui_->setUpRegularCase();
}

void CSessionSelectorOutImpl::setUpEmptyCase() {
  ui_->setUpEmptyCase();
}

void CSessionSelectorOutImpl::setUpNoSeanceCase() {
  ui_->setUpNoSeanceCase();
}

void CSessionSelectorOutImpl::updateSessionIndex() {
  SessionIndex_ = ui_->SelectionMenu()->value();
  --SessionIndex_;
  SessionIndexOutput_.notify();
}

void CSessionSelectorOutImpl::resetSessionIndex() {
  SessionIndex_ = -1;
  SessionIndexOutput_.notify();
}

QString CSessionSelectorOutImpl::getSeanceDescription(const CSeance& Seance) {
  QString Text;
  Text.append(getSeanceSizeDescription(Seance));
  for (int SessionIndex = 0; SessionIndex < Seance.size(); ++SessionIndex) {
    Text.append(getSessionDescription(SessionIndex, Seance));
  }
  return Text;
}

QString
CSessionSelectorOutImpl::getSeanceSizeDescription(const CSeance& Seance) {
  return QString("Seance size = %1\n\n").arg(Seance.size());
}

QString CSessionSelectorOutImpl::getSessionDescription(int SessionIndex,
                                                       const CSeance& Seance) {
  const CSession& Session = Seance[SessionIndex];
  return QString("%1. Session size = %2\n%3\n\n")
      .arg(SessionIndex + 1)
      .arg(Session.size())
      .arg(getSessionText(Session));
}

QString CSessionSelectorOutImpl::getSessionText(const CSession& Session) {
  QString SessionText;
  SessionScanner_.run(Session, &SessionText);
  return SessionText;
}

} // namespace NSSessionSelectorOutDetail

namespace NSSessionSelectorOut {

CSessionSelectorOut::CSessionSelectorOut(CMainWindow* MainWindow)
    : Impl_(std::make_unique<CSessionSelectorOutImpl>(MainWindow)) {
}

CSessionSelectorOut::CSessionSelectorOutImpl*
CSessionSelectorOut::operator->() {
  return Impl_.get();
}

} // namespace NSSessionSelectorOut

} // namespace NSInterface
} // namespace NSApplication
