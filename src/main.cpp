// Game loops - pong game

#include "print.h"
#include <string>
#include "Pong.h"

int main(){
    Pong pong = Pong("pong", 800, 600);

    pong.run();

}