string snake::autoMove()
{
	globalTempSnake^*this;

	static bool display=true;
	static int times=0;
	times ++;
	static int groupTime=0;

	if ((times>0 || length>2) && times%2==0)
       	{
       	         this->grow();
       	}

	if (this->isAlive()==false)
	{
//cout << "DEAD DEAD"<<endl;
		return "";
	}

	if (display==false && (times>400|| groupTime>=400))
	{
//cout << "TIMEOUT TIMEOUT"<<endl;
		return "!";
	}

	snake s1;
	s1^*this;
	snake s2;
	s2^*this;
	snake s3;
	s3^*this;
	snake s4;
	s4^*this;

	s1.move(UP);
	s2.move(DOWN);
	s3.move(LEFT);
	s4.move(RIGHT);

	if ((times>0 || length>2) && times%2==1)
       	{
		s1.grow();
		s2.grow();
		s3.grow();
   	        s4.grow();
       	}

	string count1="";
	string count2="";
	string count3="";
	string count4="";

	if(s1.isAlive()==false && s2.isAlive()==false && s3.isAlive()==false && s4.isAlive()==false)
	{
//cout << "VVVVVVVVVVVV"<<endl;
		return "!";
	}

			int tempTimes=times;
			bool tempbool=true;
			if (display==false)
			{
				tempbool=false;
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			display=false;
			if(tempTimes%2==0){times=0;}else{times=1;}
//cout << "11111"<<endl;
			count1 = s1.autoMove();
			if(tempTimes%2==0){times=0;}else{times=1;}
			if(tempbool==false)
			{
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			count2 = s2.autoMove();
			if(tempTimes%2==0){times=0;}else{times=1;}
			if (tempbool==false)
			{
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			count3 = s3.autoMove();
			if(tempTimes%2==0){times=0;}else{times=1;}
			if (tempbool==false)
			{
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			count4 = s4.autoMove();

			if(tempTimes%2==0){times=0;}else{times=1;}
			if (tempbool==true)
			{
				display=true;

			cout << "count1\t"<< count1<< "\tcount2\t"<< count2<< "\tcount3\t"<< count3<< "\tcount4\t"<< count4<<endl;

			}

	if(display==true)
	{
		system("clear");
        	drawBoard();
        	cin.get();

		if (maxCount(count1.length(),count2.length(),count3.length(),count4.length())==count1.length() && count1.length()!=0)
		{
			this->move(UP);
			return "u"+count1;
		}
		if (maxCount(count1.length(),count2.length(),count3.length(),count4.length())==count2.length() && count2.length()!=0)
		{
			this->move(DOWN);
			return "d"+count2;
		}
		if (maxCount(count1.length(),count2.length(),count3.length(),count4.length())==count3.length() && count.length()!=0)
		{
			this->move(LEFT);
			return "l"+count3;
		}
		if (maxCount(count1.length(),count2.length(),count3.length(),count4.length())==count4.length() && count4.length()!=0)
		{
			this->move(RIGHT);
			return "r"+count4;
		}
	}
}

void actualMove()
{
//start:
	string s=this->autoMove();
	for (int i=1; i<s.length(); i++)
	{
		//if (fruitExists)
		//{
			//go to fruit
		//	goto start;
		//}
		switch (s[i])
		{
			case "u": this->move(UP);
			case "d": this->move(DOWN);
			case "l": this->move(LEFT);
			case "r": this->move(RIGHT);
		}
	}
}



