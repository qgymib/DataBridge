#include <wx/wx.h>
#include <wx/socket.h>
#include "widgets/MainFrame.hpp"

class MainApp : public wxApp
{
public:
    bool OnInit() override;
    int  OnExit() override;
};

wxIMPLEMENT_APP(MainApp); // NOLINT

bool MainApp::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    // Initialize wxSocket for multiple threads usage.
    if (!wxSocketBase::Initialize())
    {
        return false;
    }

    auto frame = new DB::MainFrame(nullptr, CMAKE_PROJECT_NAME);
#if defined(_MSC_VER)
    frame->SetIcon(wxIcon("IDI_ICON1"));
#endif
    frame->Show(true);

    return true;
}

int MainApp::OnExit()
{
    wxSocketBase::Shutdown();
    return 0;
}
