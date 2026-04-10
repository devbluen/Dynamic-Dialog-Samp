
#if defined _dynamicD_included
	#endinput
#endif
#define _dynamicD_included

#if !defined _easyDialog_included
    #error "Download and install include (github.com/devbluen/easydialog_mod) and include it before this."
#endif

            // Macros
#define     DialogDynamic:%0(%1) \
                forward ddyn_%0(%1); \
                public ddyn_%0(%1)

            // Definers
#define     MAX_DIALOGDYNAMIC_ROWS      (128)

            // Includes
#include <YSI_Coding\y_hooks>

static enum E_DIALOGDYNAMIC {
    DIALOG_STYLE:E_DIALOGDYNAMIC_STYLE,
    E_DIALOGDYNAMIC_CALLBACK[32 + 1]
};

static enum E_DIALOGDYNAMICROW {
    E_DIALOGDYNAMICROW_INT,
    E_DIALOGDYNAMICROW_STRING[256 + 1]
};

static
    Iterator:DialogRows[MAX_PLAYERS]<MAX_DIALOGDYNAMIC_ROWS>,
    e_DialogDynamic[MAX_PLAYERS][E_DIALOGDYNAMIC],
    e_DialogDynamicRow[MAX_PLAYERS][MAX_DIALOGDYNAMIC_ROWS][E_DIALOGDYNAMICROW]
;

hook OnPlayerDisconnect(playerid, reason) {

    DialogDynamic_Reset(playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock DialogDynamic_Create(playerid, DIALOG_STYLE:style, const title[], const button1[], const button2[], Func:inlineCreate, const callback[]) {

    DialogDynamic_Reset(playerid);
    strcopy(e_DialogDynamic[playerid][E_DIALOGDYNAMIC_CALLBACK]);
    e_DialogDynamic[playerid][E_DIALOGDYNAMIC_STYLE] = style;

    Indirect_Claim(inlineCreate);
    @.inlineCreate();
    Indirect_Release(inlineCreate);

    new dialog[1024 * 4];
    foreach(new i: DialogRows[playerid])
        strcatEx(dialog, "%s\n", e_DialogDynamicRow[playerid][i][E_DIALOGDYNAMICROW_STRING]);

    Dialog_Show(playerid, D_DYNAMICDIALOG, style, title, dialog, button1, button2);
}

stock bool:DialogDynamic_Add(playerid, const body[], id = 0) {
    new index = Iter_Free(DialogRows[playerid]);
    if(index == ITER_NONE)
        return false;

    e_DialogDynamicRow[playerid][index][E_DIALOGDYNAMICROW_INT] = id;
    strcopy(e_DialogDynamicRow[playerid][index][E_DIALOGDYNAMICROW_STRING], body);

    Iter_Add(DialogRows[playerid], index);
    return true;
}

static stock DIALOG_STYLE:DialogDynamic_GetType(playerid)
    return e_DialogDynamic[playerid][E_DIALOGDYNAMIC_STYLE];

static stock DialogDynamic_GetInt(playerid, row)
    return e_DialogDynamicRow[playerid][row][E_DIALOGDYNAMICROW_INT];

static stock DialogDynamic_GetString(playerid, row, dest[], maxLength = sizeof dest)
    strcat(dest, e_DialogDynamicRow[playerid][row][E_DIALOGDYNAMICROW_STRING], maxLength);

static stock DialogDynamic_Reset(playerid) {

    static const e_ClearRow[E_DIALOGDYNAMICROW];
    foreach(new i: DialogRows[playerid])
        e_DialogDynamicRow[playerid][i] = e_ClearRow;

    Iter_Clear(DialogRows[playerid]);

    static const e_Clear[E_DIALOGDYNAMIC];
    e_DialogDynamic[playerid] = e_Clear;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_DYNAMICDIALOG(playerid, response, row, const inputtext[]) {

    new
        listitem,
        callback[32 + 1]
    ;

    if(DialogDynamic_GetType(playerid) == DIALOG_STYLE_TABLIST_HEADERS)
        row--;

    listitem = DialogDynamic_GetInt(playerid, row);
    DialogDynamic_GetString(playerid, row, callback);
    DialogDynamic_Reset(playerid);

    CallLocalFunction(va_return("ddyn_%s", callback), "iiis", playerid, response, listitem, inputtext);  // return -> playerid, response, listitem, inputtext[]
    return true;
}