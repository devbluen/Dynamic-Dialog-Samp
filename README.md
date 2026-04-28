# 🫧 Dynamic Dialog - System
Create options in your Dialog in a more simplified and dynamic way.

# 📜 How to install?
- You will need the YSI bookstore. (https://github.com/pawn-lang/YSI-Includes)
- You'll also need the easyDialog include; I recommend my version. (https://github.com/devbluen/easydialog_mod)
- Place the include below the easyDialog: `#include <dynamicDialog>`

# ⚙️ Functions
- `DialogDynamic_Create(playerid, DIALOG_STYLE:style, const title[], const button1[], const button2[], Func:inlineCreate, const callback[]);`
- `DialogDynamic_Add(playerid, id, const body[], {Float, _}:...);`

# 📝 Usage Examples
```pawn
enum {
    E_INTERACTION_PRIVATE_OPTION,
    E_INTERACTION_PRIVATE_OPTION_LEVEL,
    E_INTERACTION_TEST1,
    E_INTERACTION_TEST2,
    E_INTERACTION_TEST3,
E_INTERACTION_TEST4
};

public OnPlayerConnect(playerid) {

    inline DialogDynamicCreate() {

        new
            page = 1,
            pages = 2
        ;

        if(Player_IsAdmin(playerid))
            DialogDynamic_Add(playerid, E_INTERACTION_PRIVATE_OPTION, "Private Option");

        if(Player_GetLevel(playerid) >= 5)
            DialogDynamic_Add(playerid, E_INTERACTION_PRIVATE_OPTION_LEVEL, "Private Option by level");

        DialogDynamic_Add(playerid, E_INTERACTION_TEST1, "test1");
        DialogDynamic_Add(playerid, E_INTERACTION_TEST2, "test2");
        DialogDynamic_Add(playerid, E_INTERACTION_TEST3, "test3");
        DialogDynamic_Add(playerid, E_INTERACTION_TEST4, "%d/%d", page, pages);
    }

    DialogDynamic_Create(playerid, DIALOG_STYLE_TABLIST, "dynamicDialog", "Select", "Close", using inline DialogDynamicCreate, "DialogDynamicResponse");
    return true;
}

DialogDynamic:DialogDynamicResponse(playerid, response, listitem, inputtext[]) {

    if(response) {
        switch(listitem) {
            case E_INTERACTION_PRIVATE_OPTION: SendClientMessage(playerid, -1, "This is a private option.");
            case E_INTERACTION_PRIVATE_OPTION_LEVEL: SendClientMessage(playerid, -1, "This is a private option by level");
            case E_INTERACTION_TEST1: SendClientMessage(playerid, -1, "Selected Test 1");
            case E_INTERACTION_TEST2: SendClientMessage(playerid, -1, "Selected Test 2");
            case E_INTERACTION_TEST3: SendClientMessage(playerid, -1, "Selected Test 3");
            case E_INTERACTION_TEST4: SendClientMessage(playerid, -1, "Selected Test 4");
        }
    }
    return true;
}
```

# 🍪 Dependencies
- YSI-Includes: https://github.com/pawn-lang/YSI-Includes/releases
