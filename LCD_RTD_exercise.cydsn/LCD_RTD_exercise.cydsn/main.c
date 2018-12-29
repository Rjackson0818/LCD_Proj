#include <project.h>
#include <stdio.h>

#if defined (__GNUC__)
asm (".global _printf_float");
#endif

#define SCALE (1000u)

#define TEMP_SCALE (100u)

#define RTD_CHANNEL (0u)

#define CAL_CHANNEL (1u)

#define IDAC_VALUE (125u)

#define CAL_RESISTOR (100300u)

float rtdTempDisp = 0;

int main()
{

double rtdCalVoltage = 0;

uint rtdRes = 0;

static int calVoltage = 0;

uint rtdVoltage = 0;

static int calOffset = 0;

double rtdOffset = 0;

char TransmitBuffer[50];

double current = 0;

float rtdResDisp = 0;

float currentDisp = 0;

float rtdCalVoltageDisp = 0;

uint rtdTemp = 0;

ADCMux_Start();
CurrentMux_Start();
ADC_Start();
IDAC_Start();
UART_1_Start();
//Get Calibration Voltage
// Select the calibration MUX channel
CurrentMux_FastSelect(RTD_CHANNEL);
ADCMux_FastSelect(RTD_CHANNEL);
//Set IDAC to zero current
IDAC_SetValue(IDAC_VALUE);

for(;;)
{
//Read voltage across rtd resistor
ADC_StartConvert();
ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
rtdVoltage = ADC_CountsTo_mVolts(ADC_GetResult32());
ADC_StopConvert();
rtdRes = (rtdVoltage*SCALE);
rtdTemp = RTD_GetTemperature(rtdRes);
sprintf(TransmitBuffer, "rtdTemp: %u \r\n",rtdTemp);
UART_1_PutString(TransmitBuffer);
}
}