#ifdef _PAGE
    #define addButtonR(page_no, index, title, nextPage) buttons[page_no][index]._title = title; \
        buttons[page_no][index]._nextPage = nextPage;
    #define addButton(page_no, index, title) buttons[page_no][index]._title = title; \
        buttons[page_no][index]._nextPage = currPage;
#endif

#ifndef _PAGE
    #define addButtonR(page_no, index, title, nextPage)
    #define addButton(page_no, index, title)
#endif

#ifdef _CALLBACK
    #define callbacks(page_no) case page_no: switch(button) {
    #define onPress(buttonNo, code) case buttonNo: code break;
    #define endCallbacks } break;
#endif

#ifndef _CALLBACK
    #define callbacks(page_no)
    #define onPress(buttonNo, code)
    #define endCallbacks
#endif