#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnBold(wxCommandEvent& event);
    void OnItalic(wxCommandEvent& event);
    void OnChecklist(wxCommandEvent& event);
    void OnLink(wxCommandEvent& event);
    void OnBlockquote(wxCommandEvent& event);
    void OnCodeBlock(wxCommandEvent& event);
    void OnHeader(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxRichTextCtrl* textCtrl;
    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Open = 1,
    ID_Save = 2,
    ID_Bold = 3,
    ID_Italic = 4,
    ID_Checklist = 5,
    ID_Link = 6,
    ID_Blockquote = 7,
    ID_CodeBlock = 8,
    ID_Header = 9,
    ID_About = wxID_ABOUT
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Open, MyFrame::OnOpen)
    EVT_MENU(ID_Save, MyFrame::OnSave)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
    EVT_BUTTON(ID_Bold, MyFrame::OnBold)
    EVT_BUTTON(ID_Italic, MyFrame::OnItalic)
    EVT_BUTTON(ID_Checklist, MyFrame::OnChecklist)
    EVT_BUTTON(ID_Link, MyFrame::OnLink)
    EVT_BUTTON(ID_Blockquote, MyFrame::OnBlockquote)
    EVT_BUTTON(ID_CodeBlock, MyFrame::OnCodeBlock)
    EVT_BUTTON(ID_Header, MyFrame::OnHeader)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("MakeMe.md");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    textCtrl = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE);

    wxPanel* buttonPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* boldButton = new wxButton(buttonPanel, ID_Bold, "Vet");
    wxButton* italicButton = new wxButton(buttonPanel, ID_Italic, "Cursief");
    wxButton* checklistButton = new wxButton(buttonPanel, ID_Checklist, "Checklist");
    wxButton* linkButton = new wxButton(buttonPanel, ID_Link, "Link");
    wxButton* blockquoteButton = new wxButton(buttonPanel, ID_Blockquote, "Blockquote");
    wxButton* codeBlockButton = new wxButton(buttonPanel, ID_CodeBlock, "Codeblok");
    wxButton* headerButton = new wxButton(buttonPanel, ID_Header, "Header");

    buttonSizer->Add(boldButton, 0, wxALL, 5);
    buttonSizer->Add(italicButton, 0, wxALL, 5);
    buttonSizer->Add(checklistButton, 0, wxALL, 5);
    buttonSizer->Add(linkButton, 0, wxALL, 5);
    buttonSizer->Add(blockquoteButton, 0, wxALL, 5);
    buttonSizer->Add(codeBlockButton, 0, wxALL, 5);
    buttonSizer->Add(headerButton, 0, wxALL, 5);

    buttonPanel->SetSizer(buttonSizer);

    sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);
    sizer->Add(buttonPanel, 0, wxEXPAND | wxALL, 5);

    SetSizer(sizer);

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Open, "&Openen...  \tCtrl-O", "Open een Markdown-bestand");
    menuFile->Append(ID_Save, "&Opslaan... \tCtrl-S", "Sla het Markdown-bestand op");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "Afsluiten \tAlt-X", "Sluit MakeMe.md af");

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(ID_About, "&Over deze app", "Toon informatie over MakeMe.md");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&Bestand");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar(2);
    SetStatusText("Welkom bij MakeMe.md!");
}

void MyFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open Markdown-bestand"), "", "",
        "Markdown-bestanden (*.md)|*.md", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile file(openFileDialog.GetPath());
    if (!file.Exists()) {
        wxLogError("Kan het bestand '%s' niet openen.", openFileDialog.GetPath());
        return;
    }

    file.Open();
    textCtrl->Clear();
    textCtrl->SetValue(file.GetFirstLine());
    while (!file.Eof()) {
        textCtrl->AppendText("\n" + file.GetNextLine());
    }
}

void MyFrame::OnSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, _("Opslaan als Markdown-bestand"), "", "",
        "Markdown-bestanden (*.md)|*.md|", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxTextFile file(saveFileDialog.GetPath());
    if (!file.Exists()) {
        file.Create();
    } else {
        file.Open();
        file.Clear();
    }

    wxString content = textCtrl->GetValue();
    wxArrayString lines = wxSplit(content, '\n');
    for (const auto& line : lines) {
        file.AddLine(line);
    }
    file.Write();
    file.Close();
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnBold(wxCommandEvent& event) {
    long from, to;
    textCtrl->GetSelection(&from, &to);
    if (from != to) {
        wxString selectedText = textCtrl->GetStringSelection();
        selectedText.Replace("**", "");
        wxString newText = wxString::Format("**%s**", selectedText);
        textCtrl->Replace(from, to, newText);
    } else {
        textCtrl->WriteText("**Vette tekst**");
    }
}

void MyFrame::OnItalic(wxCommandEvent& event) {
    long from, to;
    textCtrl->GetSelection(&from, &to);
    if (from != to) {
        wxString selectedText = textCtrl->GetStringSelection();
        selectedText.Replace("*", "");
        wxString newText = wxString::Format("*%s*", selectedText);
        textCtrl->Replace(from, to, newText);
    } else {
        textCtrl->WriteText("*Italiaanse style tekst*");
    }
}

void MyFrame::OnChecklist(wxCommandEvent& event) {
    wxString checklist = "- [ ] Checklijst item (niet aangekruist) \n- [x] Checklijst item (aangekruist)";
    textCtrl->WriteText(checklist);
}

void MyFrame::OnLink(wxCommandEvent& event) {
    long from, to;
    textCtrl->GetSelection(&from, &to);
    wxString selectedText = textCtrl->GetStringSelection();
    wxString url = wxGetTextFromUser("Voeg een URL toe:", "Geef een link op");

    if (url.IsEmpty()) {
        wxMessageBox("Geen URL opgegeven", "Foutmelding", wxOK | wxICON_WARNING);
        textCtrl->WriteText("[Linktekst](https://www.example.com)");
    } else if (selectedText.IsEmpty()) {
        wxString newText = wxString::Format("[%s](%s)", url, url);
        textCtrl->WriteText(newText);
    } else {
        wxString newText = wxString::Format("[%s](%s)", selectedText, url);
        textCtrl->Replace(from, to, newText);
    }
}

void MyFrame::OnBlockquote(wxCommandEvent& event) {
    long from, to;
    textCtrl->GetSelection(&from, &to);
    if (from != to) {
        wxString selectedText = textCtrl->GetStringSelection();
        selectedText.Replace(">", "");
        wxString newText = wxString::Format("> %s", selectedText);
        textCtrl->Replace(from, to, newText);
    } else {
        textCtrl->WriteText("> Dit is een blockquote");
    }
}

void MyFrame::OnCodeBlock(wxCommandEvent& event) {
    wxString codeBlock = "```bash // verander naar eigen programmeer taal\n// Voeg code hier toe\n```";
    textCtrl->WriteText(codeBlock);
}

void MyFrame::OnHeader(wxCommandEvent& event) {
    long from, to;
    textCtrl->GetSelection(&from, &to);
    if (from != to) {
        wxString selectedText = textCtrl->GetStringSelection();
        wxString newText = wxString::Format("# %s", selectedText);
        textCtrl->Replace(from, to, newText);
    } else {
        textCtrl->WriteText("# Titel");
    }
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxString message = "MakeMe.md";
    message += ", een Markdown-editor gemaakt met wxWidgets. Geschreven door Tijn Rodrigo\n";
    wxMessageBox(message, "MakeMe.md (beta)", wxOK | wxICON_INFORMATION);
}
