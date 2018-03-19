//#include <QCoreApplication>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t size = 5 ;

unsigned char flipByte(unsigned char v) {
	return ((v * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
}

class Lato {
private:
	uint8_t sequence = 0;
public:
	Lato(){}
	Lato(const uint8_t val) {
		static const uint8_t max = 255 >> ( 8 - size);
		static const uint8_t maxBit = size - 2;
		static const uint8_t minBit = 2;
		auto bit = __builtin_popcount(val);
		if(bit > maxBit || val > max){
			printf("%i is too big or not enought missing bits available ! \n", val);
			exit(1);
		}
		if(bit < minBit){
			printf("%i is too small!\n", val);
			exit(1);
		}
		sequence = val;
	}
	void flip(){
		static const uint8_t po = 8 - size;
		sequence = flipByte (sequence) >> po;
	}
};

enum Pos : u_int8_t{
	top = 0,
	left = 1,
	bot = 2,
	rigth = 3
};

class Quad {
private:
	Lato sides[4];
	u_int8_t rotation = 0;
	bool flipped = false;
public:
	Quad(){}
	Quad (const Lato top, const Lato left, const Lato bot, const Lato rigth) {
		sides[Pos::top] = top;
		sides[Pos::bot] = bot;
		sides[Pos::left]= left;
		sides[Pos::rigth]= rigth;
	}
	Lato top(){
		return sides[Pos::top + rotation];
	}
	Lato bot(){
		return sides[(Pos::bot + rotation) % 4];
	}
	Lato rigth(){
		return sides[(Pos::rigth + rotation) % 4];
	}
	Lato left(){
		return sides[(Pos::left + rotation) % 4];
	}

	void rotate(uint8_t r = 0){
		rotation += r ;
		rotation = rotation % 4;
	}

	void flip(){
		flipped = !flipped;
		//all need flippin
		for (int i = 0; i < 4; ++i) {
			sides[i].flip();
		}

		//and left/right swap
		Lato buf = sides[Pos::left];
		sides[Pos::left] = sides[Pos::rigth];
		sides[Pos::rigth] = buf;
	}
	bool getFlipped() const;
};

class Set{
private:

public:
	Set(){}
	Quad q1,q2,q3,q4,q5,q6;
};

Set set;
//cosa ritorna, nome della funzione, parametri, il typedef si chiama poi delivery_function
//typedef customRuleResult (*delivery_eva)(const evaluation_condition* condition);


struct Match{




};
//#include <QElapsedTimer>
//#include <QHash>
int main(/*int argc, char *argv[]*/) {
	Quad a(0b10110,0b10100,0b01110,0b11001);


	a.flip ();

	return 0;
}

bool Quad::getFlipped() const {
	return flipped;
}
