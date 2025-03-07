#ifndef DB_WIDGETS_MAIN_FRAME_HPP
#define DB_WIDGETS_MAIN_FRAME_HPP

#include <wx/wx.h>

namespace DB
{

class MainFrame final : public wxFrame
{
public:
    MainFrame(wxWindow* parent, const char* title);
    ~MainFrame() override;

private:
    struct Data;
    Data* m_data;
};

} // namespace DB

#endif
