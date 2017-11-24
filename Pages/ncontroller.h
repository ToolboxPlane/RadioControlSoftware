#define NUM_BUTTONS 6
#define NUM_PAGES 4

namespace ncontroller {
    struct Button {
        String _title;
        int _nextPage;
    };
    Button buttons[NUM_PAGES][NUM_BUTTONS];
    int currPage;
    void init() {
        currPage = 0;
        #define _PAGE
        #include "pages.hpp"
        #undef _PAGE
    }

    void buttonHandler(uint8_t button) {
        switch(currPage) {
            #define _CALLBACK
            #include "pages.hpp"
            #undef _CALLBACK
        }
        currPage = buttons[currPage][button]._nextPage;
    }
}
#undef _NCONTROLLER
