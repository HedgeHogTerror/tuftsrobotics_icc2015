#ifndef RMCS2203_H
#define RMCS2203_H

class RMCS2203{

public:
	RMCS2203(int addr); //Constructor
	
	void setSpeed(int speed);
	int getSpeed();
	
	void setMaxSpeed(int maxSpeed);
	int getMaxSpeed();
	
	void setSpeedDamping(int damping);
	int getSpeedDamping();
	
	void setPosition(long pos);
	long getPosition();
	void goToAbsPosition(long absPos);
	void goToRelPosition(long relPos);
	
	void setSpeedFeedbackGain(int gain);
	int getSpeedFeedbackGain();
	
	void setPGain(int gain);
	int getPGain();
	
	void setIGain(int gain);
	int getIGain();
	
private:
	int address;

#endif