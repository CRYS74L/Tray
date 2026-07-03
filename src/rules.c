#include "rules.h"

#include <wctype.h>

typedef struct TrayRule {
    const wchar_t *exe_name;
    const wchar_t *class_prefix;
    unsigned int uid;
} TrayRule;

static const TrayRule kRules[] = {
    { L"LYRICIFY LITE.EXE", L"H.NotifyIcon_", 0 },
    { L"BETTERLYRICS.WINUI3.EXE", L"H.NotifyIcon_", 0 },
    { L"EXPLORER.EXE", L"ATL:", 100 },
};

static int equals_ignore_case(const wchar_t *a, const wchar_t *b) {
    if (!a || !b) {
        return 0;
    }

    while (*a && *b) {
        if (towupper(*a) != towupper(*b)) {
            return 0;
        }
        ++a;
        ++b;
    }

    return *a == L'\0' && *b == L'\0';
}

static int starts_with(const wchar_t *value, const wchar_t *prefix) {
    if (!value || !prefix) {
        return 0;
    }

    while (*prefix) {
        if (*value != *prefix) {
            return 0;
        }
        ++value;
        ++prefix;
    }

    return 1;
}

int tray_rule_matches(const wchar_t *exe_name, const wchar_t *class_name, unsigned int uid) {
    if (!exe_name || !class_name) {
        return 0;
    }

    for (int i = 0; i < tray_rule_count(); ++i) {
        if (uid == kRules[i].uid &&
            equals_ignore_case(exe_name, kRules[i].exe_name) &&
            starts_with(class_name, kRules[i].class_prefix)) {
            return 1;
        }
    }

    return 0;
}

int tray_rule_uid_for_window(const wchar_t *exe_name, const wchar_t *class_name, unsigned int *uid) {
    if (!exe_name || !class_name || !uid) {
        return 0;
    }

    for (int i = 0; i < tray_rule_count(); ++i) {
        if (equals_ignore_case(exe_name, kRules[i].exe_name) &&
            starts_with(class_name, kRules[i].class_prefix)) {
            *uid = kRules[i].uid;
            return 1;
        }
    }

    return 0;
}

int tray_rule_process_is_target(const wchar_t *exe_name) {
    if (!exe_name) {
        return 0;
    }

    for (int i = 0; i < tray_rule_count(); ++i) {
        if (equals_ignore_case(exe_name, kRules[i].exe_name)) {
            return 1;
        }
    }

    return 0;
}

int tray_rule_count(void) {
    return (int)(sizeof(kRules) / sizeof(kRules[0]));
}

const wchar_t *tray_rule_exe(int index) {
    if (index < 0 || index >= tray_rule_count()) {
        return L"";
    }
    return kRules[index].exe_name;
}

const wchar_t *tray_rule_class_name(int index) {
    if (index < 0 || index >= tray_rule_count()) {
        return L"";
    }
    return kRules[index].class_prefix;
}

unsigned int tray_rule_uid(int index) {
    if (index < 0 || index >= tray_rule_count()) {
        return 0;
    }
    return kRules[index].uid;
}
