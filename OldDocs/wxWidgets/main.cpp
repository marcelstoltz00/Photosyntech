#include <wx/wx.h>
#include <vector>
#include <string>

class BasicFrame : public wxFrame {
public:
    BasicFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets Basic Example",
                          wxDefaultPosition, wxSize(500, 400)) {
        CreateControls();
        BindEvents();

        // Center the window
        Centre();
    }

private:
    void CreateControls() {
        // Create main panel
        wxPanel* panel = new wxPanel(this);

        // Create main sizer
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Title
        wxStaticText* title = new wxStaticText(panel, wxID_ANY,
            "wxWidgets Basic UI Demo", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        wxFont titleFont = title->GetFont();
        titleFont.SetPointSize(16);
        titleFont.SetWeight(wxFONTWEIGHT_BOLD);
        title->SetFont(titleFont);
        mainSizer->Add(title, 0, wxALL | wxCENTER, 10);

        // Input section
        wxStaticBoxSizer* inputSizer = new wxStaticBoxSizer(wxVERTICAL, panel, "Text Input");

        wxBoxSizer* inputRowSizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* inputLabel = new wxStaticText(panel, wxID_ANY, "Enter text:");
        textInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition,
                                  wxDefaultSize, wxTE_PROCESS_ENTER);
        textInput->SetHint("Type something here...");

        inputRowSizer->Add(inputLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        inputRowSizer->Add(textInput, 1, wxALL | wxEXPAND, 5);
        inputSizer->Add(inputRowSizer, 0, wxEXPAND);

        // Buttons
        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        addButton = new wxButton(panel, wxID_ANY, "Add Text");
        clearButton = new wxButton(panel, wxID_ANY, "Clear All");

        buttonSizer->Add(addButton, 0, wxALL, 5);
        buttonSizer->Add(clearButton, 0, wxALL, 5);
        inputSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

        mainSizer->Add(inputSizer, 0, wxALL | wxEXPAND, 10);

        // Text display
        wxStaticBoxSizer* displaySizer = new wxStaticBoxSizer(wxVERTICAL, panel, "Text Entries");
        textDisplay = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition,
                                    wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
        textDisplay->SetHint("Your text entries will appear here...");

        displaySizer->Add(textDisplay, 1, wxALL | wxEXPAND, 5);
        mainSizer->Add(displaySizer, 1, wxALL | wxEXPAND, 10);

        // Status section
        wxBoxSizer* statusSizer = new wxBoxSizer(wxHORIZONTAL);
        statusText = new wxStaticText(panel, wxID_ANY, "Ready");
        statusSizer->Add(statusText, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);

        mainSizer->Add(statusSizer, 0, wxALL | wxEXPAND, 5);

        panel->SetSizer(mainSizer);

        // Create menu bar
        CreateMenuBar();

        // Create status bar
        CreateStatusBar();
        SetStatusText("wxWidgets Basic Example - Ready");
    }

    void CreateMenuBar() {
        wxMenuBar* menuBar = new wxMenuBar();

        // File menu
        wxMenu* fileMenu = new wxMenu();
        fileMenu->Append(wxID_NEW, "&New\tCtrl+N", "Clear all text");
        fileMenu->AppendSeparator();
        fileMenu->Append(wxID_EXIT, "E&xit\tCtrl+Q", "Exit the application");

        // Help menu
        wxMenu* helpMenu = new wxMenu();
        helpMenu->Append(wxID_ABOUT, "&About\tF1", "About this application");

        menuBar->Append(fileMenu, "&File");
        menuBar->Append(helpMenu, "&Help");

        SetMenuBar(menuBar);
    }

    void BindEvents() {
        // Button events
        Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BasicFrame::OnAddText, this, addButton->GetId());
        Bind(wxEVT_COMMAND_BUTTON_CLICKED, &BasicFrame::OnClearText, this, clearButton->GetId());

        // Text input enter key
        Bind(wxEVT_COMMAND_TEXT_ENTER, &BasicFrame::OnAddText, this, textInput->GetId());

        // Menu events
        Bind(wxEVT_COMMAND_MENU_SELECTED, &BasicFrame::OnClearText, this, wxID_NEW);
        Bind(wxEVT_COMMAND_MENU_SELECTED, &BasicFrame::OnExit, this, wxID_EXIT);
        Bind(wxEVT_COMMAND_MENU_SELECTED, &BasicFrame::OnAbout, this, wxID_ABOUT);
    }

    void OnAddText(wxCommandEvent& event) {
        wxString text = textInput->GetValue();
        if (!text.IsEmpty()) {
            textEntries.push_back(text.ToStdString());
            UpdateDisplay();
            textInput->Clear();
            textInput->SetFocus();

            statusText->SetLabel(wxString::Format("Added entry #%zu", textEntries.size()));
            SetStatusText(wxString::Format("Total entries: %zu", textEntries.size()));
        } else {
            wxMessageBox("Please enter some text!", "Warning", wxOK | wxICON_WARNING, this);
        }
    }

    void OnClearText(wxCommandEvent& event) {
        if (!textEntries.empty()) {
            wxMessageDialog dialog(this,
                wxString::Format("Clear all %zu text entries?", textEntries.size()),
                "Confirm Clear", wxYES_NO | wxICON_QUESTION);

            if (dialog.ShowModal() == wxID_YES) {
                textEntries.clear();
                UpdateDisplay();
                statusText->SetLabel("All entries cleared");
                SetStatusText("Ready");
            }
        }
    }

    void OnExit(wxCommandEvent& event) {
        Close(true);
    }

    void OnAbout(wxCommandEvent& event) {
        wxMessageBox("wxWidgets Basic UI Example\n\n"
                    "Demonstrates basic wxWidgets functionality:\n"
                    "• Text input and display\n"
                    "• Button handling\n"
                    "• Menu system\n"
                    "• Status bar\n"
                    "• Message dialogs",
                    "About", wxOK | wxICON_INFORMATION, this);
    }

    void UpdateDisplay() {
        wxString displayText;
        for (size_t i = 0; i < textEntries.size(); i++) {
            displayText += wxString::Format("%zu: %s\n", i + 1, textEntries[i]);
        }
        textDisplay->SetValue(displayText);
    }

    // Controls
    wxTextCtrl* textInput;
    wxButton* addButton;
    wxButton* clearButton;
    wxTextCtrl* textDisplay;
    wxStaticText* statusText;

    // Data
    std::vector<std::string> textEntries;
};

class BasicApp : public wxApp {
public:
    bool OnInit() override {
        BasicFrame* frame = new BasicFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(BasicApp);