/**
 * @file Ansi-color-codes.h
 * @brief ANSI escape code definitions for terminal text coloring and formatting
 * @author Michael Tomlinson
 * @date 2025/08/01
 *
 * This header file provides a comprehensive set of ANSI escape code macros
 * for terminal text formatting including colors, bold text, underlined text,
 * background colors, and high intensity variants. These codes are used to
 * enhance the visual presentation of the PetSpace chat application's console output.
 *
 * @note ANSI codes may not be supported on all terminal emulators
 * @note Use CRESET or COLOR_RESET to return text formatting to normal
 */

// Regular text colors
#define BLK "\e[0;30m"      ///< Black text
#define RED "\e[0;31m"      ///< Red text
#define GRN "\e[0;32m"      ///< Green text
#define YEL "\e[0;33m"      ///< Yellow text
#define BLU "\e[0;34m"      ///< Blue text
#define MAG "\e[0;35m"      ///< Magenta text
#define CYN "\e[0;36m"      ///< Cyan text
#define WHT "\e[0;37m"      ///< White text

// Bold text colors
#define BBLK "\e[1;30m"     ///< Bold black text
#define BRED "\e[1;31m"     ///< Bold red text
#define BGRN "\e[1;32m"     ///< Bold green text
#define BYEL "\e[1;33m"     ///< Bold yellow text
#define BBLU "\e[1;34m"     ///< Bold blue text
#define BMAG "\e[1;35m"     ///< Bold magenta text
#define BCYN "\e[1;36m"     ///< Bold cyan text
#define BWHT "\e[1;37m"     ///< Bold white text

// Underlined text colors
#define UBLK "\e[4;30m"     ///< Underlined black text
#define URED "\e[4;31m"     ///< Underlined red text
#define UGRN "\e[4;32m"     ///< Underlined green text
#define UYEL "\e[4;33m"     ///< Underlined yellow text
#define UBLU "\e[4;34m"     ///< Underlined blue text
#define UMAG "\e[4;35m"     ///< Underlined magenta text
#define UCYN "\e[4;36m"     ///< Underlined cyan text
#define UWHT "\e[4;37m"     ///< Underlined white text

// Background colors
#define BLKB "\e[40m"       ///< Black background
#define REDB "\e[41m"       ///< Red background
#define GRNB "\e[42m"       ///< Green background
#define YELB "\e[43m"       ///< Yellow background
#define BLUB "\e[44m"       ///< Blue background
#define MAGB "\e[45m"       ///< Magenta background
#define CYNB "\e[46m"       ///< Cyan background
#define WHTB "\e[47m"       ///< White background

// High intensity background colors
#define BLKHB "\e[0;100m"   ///< High intensity black background
#define REDHB "\e[0;101m"   ///< High intensity red background
#define GRNHB "\e[0;102m"   ///< High intensity green background
#define YELHB "\e[0;103m"   ///< High intensity yellow background
#define BLUHB "\e[0;104m"   ///< High intensity blue background
#define MAGHB "\e[0;105m"   ///< High intensity magenta background
#define CYNHB "\e[0;106m"   ///< High intensity cyan background
#define WHTHB "\e[0;107m"   ///< High intensity white background

// High intensity text colors
#define HBLK "\e[0;90m"     ///< High intensity black text
#define HRED "\e[0;91m"     ///< High intensity red text
#define HGRN "\e[0;92m"     ///< High intensity green text
#define HYEL "\e[0;93m"     ///< High intensity yellow text
#define HBLU "\e[0;94m"     ///< High intensity blue text
#define HMAG "\e[0;95m"     ///< High intensity magenta text
#define HCYN "\e[0;96m"     ///< High intensity cyan text
#define HWHT "\e[0;97m"     ///< High intensity white text

// Bold high intensity text colors
#define BHBLK "\e[1;90m"    ///< Bold high intensity black text
#define BHRED "\e[1;91m"    ///< Bold high intensity red text
#define BHGRN "\e[1;92m"    ///< Bold high intensity green text
#define BHYEL "\e[1;93m"    ///< Bold high intensity yellow text
#define BHBLU "\e[1;94m"    ///< Bold high intensity blue text
#define BHMAG "\e[1;95m"    ///< Bold high intensity magenta text
#define BHCYN "\e[1;96m"    ///< Bold high intensity cyan text
#define BHWHT "\e[1;97m"    ///< Bold high intensity white text

// Intense black text on various intense backgrounds
#define BHBLK_ON_REDHB   "\e[1;30;101m"  ///< Bold black text on high intensity red background
#define BHBLK_ON_GRNHB   "\e[1;30;102m"  ///< Bold black text on high intensity green background
#define BHBLK_ON_YELHB   "\e[1;30;103m"  ///< Bold black text on high intensity yellow background
#define BHBLK_ON_BLUHB   "\e[1;30;104m"  ///< Bold black text on high intensity blue background
#define BHBLK_ON_MAGHB   "\e[1;30;105m"  ///< Bold black text on high intensity magenta background
#define BHBLK_ON_CYNHB   "\e[1;30;106m"  ///< Bold black text on high intensity cyan background
#define BHBLK_ON_WHTHB   "\e[1;30;107m"  ///< Bold black text on high intensity white background

// Reset codes to return formatting to normal
#define CRESET "\e[0m"      ///< Reset all text formatting to default
#define COLOR_RESET "\e[0m" ///< Reset all text formatting to default (alternative name)
