#include "Application.h"

#include "ApplicationImpl.h"


namespace NSApplication {

CApplication::CApplication() : AppImpl_(std::make_unique<CApplicationImpl>()) {
}

CApplication::~CApplication() = default;

} // NSApplication
