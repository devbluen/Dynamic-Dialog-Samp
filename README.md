# 🍪 Dynamic Dialog - System
Stop using loops and logic that will hinder your performance. The dynamicDialog solves the problem of dynamic selection in dialogs, making it easier for you to know which item has been selected.

# 🫧 How to install?
- You will need the YSI bookstore. (https://github.com/pawn-lang/YSI-Includes)
- You'll also need the easyDialog include; I recommend my version. (https://github.com/devbluen/easydialog_mod)
- Place the include below the easyDialog: `#include <dynamicDialog>`

# ⚙️ Functions
- `DialogDynamic_Create(playerid, DIALOG_STYLE:style, const title[], const button1[], const button2[], Func:inlineCreate, const callback[])`
- `DialogDynamic_Add(playerid, const body[], id = 0)`

# 📝 Usage Examples
```pawn
enum {
    E_INTERACTION_PRIVATE_OPTION,
    E_INTERACTION_PRIVATE_OPTION_LEVEL,
    E_INTERACTION_TEST1,
    E_INTERACTION_TEST2,
    E_INTERACTION_TEST3
};

public OnPlayerConnect(playerid) {

    inline DialogDynamicCreate() {

        if(Player_IsAdmin(playerid))
            DialogDynamic_Add(playerid, "Private Option", E_INTERACTION_PRIVATE_OPTION);

        if(Player_GetLevel(playerid) >= 5)
            DialogDynamic_Add(playerid, "Private Option by level", E_INTERACTION_PRIVATE_OPTION_LEVEL);

        DialogDynamic_Add(playerid, "test1", E_INTERACTION_TEST1);
        DialogDynamic_Add(playerid, "test2", E_INTERACTION_TEST2);
        DialogDynamic_Add(playerid, "test3", E_INTERACTION_TEST3);
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
        }
    }
    return true;
}
```
