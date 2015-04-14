#ifndef RMCS2203_H
#define RMCS2203_H

class RMCS2203{

public:
	RMCS2203(); //Constructor
	
	void attach(int addr);
        
        //Sets all gains to nominal values
        void calibrate();
	
	void setSpeed(int speed);
	int getSpeed();
	
	void setMaxSpeed(int maxSpeed);
	int getMaxSpeed();
	
	void setSpeedDamping(int damping);
	int getSpeedDamping();
	
	void setPosition(long pos);
        void calibrateZeroPosition();
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
	
};

#endif
