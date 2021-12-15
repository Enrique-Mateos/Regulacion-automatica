#include <Servo.h>

Servo var;

int Outvar=0;
int OutvarM=0;
int InputM=0;
int Input = 0;


void setup()
{
Serial.begin(115200);
var.attach(9); //pin de arduino que inyectara la señal PWM al variador
var.writeMicroseconds(630);//se inicializa el variador, en caso de conectar arduino despues de tener ya alimentado el variador
delay(3000);//le damos un tiempo prudente para la inicializacion
}

void loop()
{
Input = analogRead(A0);//realizamos la lectura analogica en el pin A0
InputM=map(Input, 0, 1023, 0, 255);//convertimos la señal obtenida del CAD de 10 bits a una señal de 8 bits
Serial.write(InputM);//Enviamos la lecuta del potencimetro a Simulink.

//Leemos el puerto para obtener los datos que nos envia Simulink
 if(Serial.available()){
 Outvar = Serial.read();
  }

//convertimos la señal recibida de simulink que oscila entre 0 y 255, en la señal que nos interesa para controlar el motor.
OutvarM = map(Outvar, 0, 255, 630, 885);//el valor maximo que enviamos al motor es 885 porque es mas que suficiente para generar empuje en cualquier situacion
//pero podria alcanzar el valor 2000 donde se obtiene toda la potencia que desempeña el motor 

var.writeMicroseconds(OutvarM);

//este If es para hacer un apagado suave del motor
 if(Serial.available()==0){
  if (Outvar>0){
 Outvar--;
 var.writeMicroseconds(OutvarM);
 delay(50);
   }
 }
 //Con este delay obtenemos un mejor desempeño.
delay(20);
}
