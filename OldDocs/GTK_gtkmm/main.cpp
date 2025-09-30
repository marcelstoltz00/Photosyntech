#include <gtkmm.h>
#include <vector>
#include <string>

class BasicWindow : public Gtk::Window {
public:
    BasicWindow() {
        set_title("GTK (gtkmm) Basic Example");
        set_default_size(450, 350);
        set_border_width(10);

        setupUI();
        connectSignals();
    }

private:
    void setupUI() {
        // Main vertical box
        vbox_main.set_spacing(10);
        add(vbox_main);

        // Title label
        title_label.set_markup("<big><b>GTK (gtkmm) Basic UI Demo</b></big>");
        title_label.set_halign(Gtk::ALIGN_CENTER);
        vbox_main.pack_start(title_label, Gtk::PACK_SHRINK);

        // Input frame
        input_frame.set_label("Text Input");
        input_frame.set_border_width(5);
        vbox_main.pack_start(input_frame, Gtk::PACK_SHRINK);

        // Input container
        input_vbox.set_spacing(5);
        input_vbox.set_border_width(10);
        input_frame.add(input_vbox);

        // Input row
        input_hbox.set_spacing(5);
        input_vbox.pack_start(input_hbox, Gtk::PACK_SHRINK);

        input_label.set_text("Enter text:");
        input_hbox.pack_start(input_label, Gtk::PACK_SHRINK);

        text_entry.set_placeholder_text("Type something here...");
        input_hbox.pack_start(text_entry, Gtk::PACK_EXPAND_WIDGET);

        // Button row
        button_hbox.set_spacing(5);
        button_hbox.set_halign(Gtk::ALIGN_CENTER);
        input_vbox.pack_start(button_hbox, Gtk::PACK_SHRINK);

        add_button.set_label("Add Text");
        clear_button.set_label("Clear All");
        button_hbox.pack_start(add_button, Gtk::PACK_SHRINK);
        button_hbox.pack_start(clear_button, Gtk::PACK_SHRINK);

        // Display frame
        display_frame.set_label("Text Entries");
        display_frame.set_border_width(5);
        vbox_main.pack_start(display_frame, Gtk::PACK_EXPAND_WIDGET);

        // Scrolled window for text view
        scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        display_frame.add(scrolled_window);

        // Text view
        text_buffer = Gtk::TextBuffer::create();
        text_view.set_buffer(text_buffer);
        text_view.set_editable(false);
        text_view.set_cursor_visible(false);
        text_view.set_border_width(5);
        scrolled_window.add(text_view);

        // Status bar
        status_label.set_text("Ready");
        status_label.set_halign(Gtk::ALIGN_START);
        vbox_main.pack_start(status_label, Gtk::PACK_SHRINK);

        // Show all widgets
        show_all_children();
    }

    void connectSignals() {
        add_button.signal_clicked().connect(
            sigc::mem_fun(*this, &BasicWindow::on_add_clicked));
        clear_button.signal_clicked().connect(
            sigc::mem_fun(*this, &BasicWindow::on_clear_clicked));
        text_entry.signal_activate().connect(
            sigc::mem_fun(*this, &BasicWindow::on_add_clicked));
    }

    void on_add_clicked() {
        Glib::ustring text = text_entry.get_text();
        if (!text.empty()) {
            text_entries.push_back(text);
            updateDisplay();
            text_entry.set_text("");
            text_entry.grab_focus();

            status_label.set_text("Added entry #" + std::to_string(text_entries.size()));
        } else {
            showWarningDialog("Please enter some text!");
        }
    }

    void on_clear_clicked() {
        if (!text_entries.empty()) {
            Gtk::MessageDialog dialog(*this,
                "Clear all " + std::to_string(text_entries.size()) + " text entries?",
                false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
            dialog.set_secondary_text("This action cannot be undone.");

            int result = dialog.run();
            if (result == Gtk::RESPONSE_YES) {
                text_entries.clear();
                updateDisplay();
                status_label.set_text("All entries cleared");
            }
        } else {
            showInfoDialog("No entries to clear.");
        }
    }

    void updateDisplay() {
        std::string display_text;
        for (size_t i = 0; i < text_entries.size(); i++) {
            display_text += std::to_string(i + 1) + ": " + text_entries[i] + "\n";
        }

        text_buffer->set_text(display_text);

        // Scroll to bottom
        auto iter = text_buffer->end();
        text_view.scroll_to(iter);
    }

    void showWarningDialog(const std::string& message) {
        Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_WARNING);
        dialog.run();
    }

    void showInfoDialog(const std::string& message) {
        Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_INFO);
        dialog.run();
    }

    // Layout containers
    Gtk::VBox vbox_main;
    Gtk::Frame input_frame;
    Gtk::VBox input_vbox;
    Gtk::HBox input_hbox;
    Gtk::HBox button_hbox;
    Gtk::Frame display_frame;
    Gtk::ScrolledWindow scrolled_window;

    // Widgets
    Gtk::Label title_label;
    Gtk::Label input_label;
    Gtk::Entry text_entry;
    Gtk::Button add_button;
    Gtk::Button clear_button;
    Gtk::TextView text_view;
    Gtk::Label status_label;

    // Text buffer
    Glib::RefPtr<Gtk::TextBuffer> text_buffer;

    // Data
    std::vector<std::string> text_entries;
};

class BasicApp : public Gtk::Application {
protected:
    BasicApp() : Gtk::Application("org.example.gtkmm.basicapp") {}

public:
    static Glib::RefPtr<BasicApp> create() {
        return Glib::RefPtr<BasicApp>(new BasicApp());
    }

protected:
    void on_activate() override {
        auto window = new BasicWindow();
        add_window(*window);
        window->present();
    }
};

int main(int argc, char* argv[]) {
    auto app = BasicApp::create();
    return app->run(argc, argv);
}