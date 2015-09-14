// quadcopter.c

#include "quadcopter.h"

//height desired to maintain
#define MAINTAIN_HEIGHT 100

//store the last thrust values
int8_t lastFR = 20;
int8_t lastFL = 20;
int8_t lastBR = 20;
int8_t lastBL = 20;

int main(int argc, char* argv[])
{
	while (1) {
		uint8_t pitch = getPitch();
		uint8_t roll = getRoll();

		/*Goal : maintain the pitch and roll at zero and height at MAINTAIN_HEIGHT*/
		/* Pitch : forward/backword, Roll : side*/

		//it is leaning forward
		if (pitch > 0) {
			/* we need to increase the speed of front left and right motors*/
			setFL(lastFL++);
			setFR(lastFR++);
		}
		//it is leaning backwards
		else if (pitch < 0) {
			/* we need to increase the speed of back left and right motors*/
			setBL(lastBL++);
			setBR(lastBR++);
		}

		//it is leaning right
		if (roll > 0) {
			/* we need to increase the speed of front right and back right*/
			setFR(lastFR++);
			setBR(lastBR++);
		}
		//it is leaning left
		else if (pitch < 0) {
			/* we need to increase the speed of front left and back left*/
			setFL(lastFL++);
			setBL(lastBL++);
		}

		/*check the height now*/
		uint8_t height = getHeight();

		/*check whether the height is at the desired position*/
		if (roll > MAINTAIN_HEIGHT) {
			setFR(lastFR--);
			setBR(lastBR--);
			setFL(lastFL--);
			setBL(lastBL--);

		}
		else if (roll < MAINTAIN_HEIGHT) {
			setFR(lastFR++);
			setBR(lastBR++);
			setFL(lastFL++);
			setBL(lastBL++);
		}
	}

	return 0;
}

