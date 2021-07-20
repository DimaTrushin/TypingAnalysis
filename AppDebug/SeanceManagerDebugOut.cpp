#include "SeanceManagerDebugOut.h"

#include "AppDebug/SeanceManagerDebugGUI.h"

#include <QTextEdit>

namespace NSAppDebug {

namespace NSSeanceManagerDebugOutDetail {
CSeanceManagerDebugOutImpl::CSeanceManagerDebugOutImpl(CMainWindow* MainWindow)
    : ui_(std::make_unique<CSeanceManagerDebugGUI>(MainWindow)),
      CurrentSeanceTreeView_(ui_->TreeView()),
      CurrentSeanceInput_(
          [this](const CSeance& Seance) { outputCurrentSeance(Seance); }) {
}

CSeanceManagerDebugOutImpl::~CSeanceManagerDebugOutImpl() = default;

CSeanceManagerDebugOutImpl::CSeanceObserver*
CSeanceManagerDebugOutImpl::currentSeanceInput() {
  return &CurrentSeanceInput_;
}

CSeanceManagerDebugOutImpl::CSeanceObserver*
CSeanceManagerDebugOutImpl::currentSeanceTreeInput() {
  return CurrentSeanceTreeView_->currentSeanceInput();
}

void CSeanceManagerDebugOutImpl::outputCurrentSeance(
    const CSeanceManagerDebugOutImpl::CSeance& Seance) {
  QString Text = QString("Seance size = %1\n").arg(Seance.size());
  for (const auto& session : Seance) {
    QString SessionText = QString("  Session size = %1\n  |%2|\n")
                              .arg(session.size(), 2, 10)
                              .arg(getSessionText(session));
    Text.append(SessionText);
  }
  ui_->Text()->setText(Text);
}

QString CSeanceManagerDebugOutImpl::getSessionText(const CSession& Session) {
  QString Text;
  for (const auto& element : Session) {
    Text.append(QString(element.getText().Symbol, element.getText().Size) !=
                        QString()
                    ? QString(element.getText().Symbol, element.getText().Size)
                    : element.getLabel().LowSymbol);
  }
  return Text;
}

} // namespace NSSeanceManagerDebugOutDetail

CSeanceManagerDebugOut::CSeanceManagerDebugOut(CMainWindow* MainWindow)
    : Impl_(std::make_unique<CSeanceManagerDebugOutImpl>(MainWindow)) {
}

CSeanceManagerDebugOut::CSeanceManagerDebugOutImpl*
CSeanceManagerDebugOut::operator->() {
  return Impl_.get();
}

} // namespace NSAppDebug
