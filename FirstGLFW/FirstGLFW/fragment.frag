#version 330


uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

uniform vec4 secondHandColor;
uniform vec4 minuteHandColor;
uniform vec4 hourHandColor;



layout  (location = 0) out vec4 color;
varying vec2 vPos;


void main(){

	color = vec4(1.0, 1.0, 1.0, 1.0);
	 
	float distance = length(vPos);

	if( distance <= 0.9){
		color = vec4(1.0, 1.0, 1.0, 1.0);		
	}

	//SecondHand
	float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer),sin(currentSecondPointer)));
	if(distance >= 0.2 && distance <= 0.3 && dotSecond <  sin(currentSecondPointer)){
		color = secondHandColor;
	}

	//Minute Hand
	float dotMinute = dot(normalize(vPos), vec2(0.6 * cos(currentMinutePointer), 0.6 *sin(currentMinutePointer)));
	if(distance >= 0.4 && distance <= 0.5 && dotMinute < 0.6 * sin(currentMinutePointer)){
		color = minuteHandColor;
	}
	
	//Hour Hand       
	float dotHour = dot(normalize(vPos), vec2(0.8 * cos(currentHourPointer),0.8 * sin(currentHourPointer)));
	if(distance >0.6 && distance <= 0.7 && dotHour < 0.8 * sin(currentHourPointer)){
		color = hourHandColor;
	} 

	
}