#include <wx/wx.h>
#include <wx/artprov.h>
#include "MainFrame.hpp"
#include "protocol/socks5.hpp"

struct DB::MainFrame::Data
{
    explicit Data(MainFrame* owner);
    void OnAbout(wxCommandEvent&);
    void OnNew(wxCommandEvent&);

    MainFrame*   owner;
    wxToolBar*   toolBar;
    wxStatusBar* statusBar;
};

DB::MainFrame::Data::Data(MainFrame* owner)
{
    this->owner = owner;

    {
        auto menuBar = new wxMenuBar;

        auto menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);
        menuHelp->Bind(wxEVT_MENU, &Data::OnAbout, this, wxID_ABOUT);
        menuBar->Append(menuHelp, _("Help"));

        owner->SetMenuBar(menuBar);
    }

    toolBar = owner->CreateToolBar();
    toolBar->AddTool(wxID_NEW, _("New"), wxArtProvider::GetBitmap(wxART_NEW));
    toolBar->Bind(wxEVT_TOOL, &Data::OnNew, this, wxID_NEW);
    toolBar->Realize();

    statusBar = owner->CreateStatusBar();
}

void DB::MainFrame::Data::OnAbout(wxCommandEvent&)
{
}

void DB::MainFrame::Data::OnNew(wxCommandEvent&)
{
    Socks5::Option opt;
    Socks5 sock(opt);
}

DB::MainFrame::MainFrame(wxWindow* parent, const char* title) : wxFrame(parent, wxID_ANY, title)
{
    m_data = new Data(this);
}

DB::MainFrame::~MainFrame()
{
    delete m_data;
}
