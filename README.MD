## Descriere Proiect
Acest proiect implementează un sistem automat de irigare a plantelor utilizând un NodeMCU ESP8266 și platforma Blynk pentru monitorizare și control în timp real. Sistemul folosește mai mulți senzori pentru a monitoriza condițiile ambientale și controlează o pompă de apă pentru a asigura umiditatea optimă a solului.

## Componente Utilizate
- NodeMCU ESP8266
- Senzor de umiditate și temperatură DHT11
- Senzor de umiditate a solului
- Senzor de luminozitate (LDR)
- Senzor ultrasonic HC-SR04
- Releu pentru controlul pompei de apă
- Pompă de apă submersibilă
- Blynk App pentru monitorizare și control

## Biblioteci Necesare
1. **ESP8266WiFi.h**: Permite conectarea NodeMCU la rețeaua WiFi.
2. **BlynkSimpleEsp8266.h**: Oferă integrarea cu platforma Blynk pentru IoT.
3. **DHT.h**: Permite interfațarea cu senzorii de temperatură și umiditate DHT.
4. **NewPing.h**: Gestionarea eficientă a senzorului ultrasonic HC-SR04.

### Instalare Biblioteci
Toate bibliotecile necesare pot fi instalate prin Library Manager în Arduino IDE:
1. **ESP8266WiFi**: Instalată automat cu ESP8266 core.
2. **Blynk**: Căutați "Blynk" și instalați "Blynk by Volodymyr Shymanskyy".
3. **DHT sensor library**: Căutați "DHT sensor library" și instalați "DHT sensor library by Adafruit".
4. **NewPing**: Căutați "NewPing" și instalați "NewPing by Tim Eckel".

## Conexiuni Hardware
1. **NodeMCU ESP8266**:
   - **VIN**: Conectat la alimentarea externă de 5V.
   - **GND**: Conectat la masa comună (GND).

2. **DHT11**:
   - **VCC**: Conectat la 3V3 pe NodeMCU.
   - **GND**: Conectat la GND pe NodeMCU.
   - **Data**: Conectat la D1 (GPIO5) pe NodeMCU.

3. **Senzor de Umiditate a Solului**:
   - **VCC**: Conectat la 3V3 pe NodeMCU.
   - **GND**: Conectat la GND pe NodeMCU.
   - **AO**: Conectat la A0 pe NodeMCU.

4. **LDR (Fotorezistor)**:
   - **Un capăt al LDR**: Conectat la 3V3 pe NodeMCU.
   - **Celălalt capăt al LDR**: Conectat la un divizor de tensiune (rezistor conectat la GND).
   - **Punctul comun al divizorului de tensiune**: Conectat la A0 pe NodeMCU.

5. **HC-SR04 (Senzor Ultrasonic)**:
   - **VCC**: Conectat la 5V pe breadboard (alimentare externă).
   - **GND**: Conectat la GND pe breadboard.
   - **Trig**: Conectat la D2 (GPIO4) pe NodeMCU.
   - **Echo**: Conectat la D3 (GPIO0) pe NodeMCU.

6. **Releu**:
   - **VCC**: Conectat la 3V3 pe NodeMCU.
   - **GND**: Conectat la GND pe NodeMCU.
   - **IN**: Conectat la D5 (GPIO14) pe NodeMCU.
   - **COM**: Conectat la terminalul pozitiv al sursei de alimentare a pompei.
   - **NO**: Conectat la terminalul pozitiv al pompei.

7. **Pompa de Apă**:
   - **Fir pozitiv**: Conectat la NO (Normally Open) pe releu.
   - **Fir negativ**: Conectat la GND al sursei de alimentare externe.

## Configurare Blynk
1. **Descarcă și Instalează Blynk App** din App Store (iOS) sau Google Play (Android).
2. **Crează un nou proiect** și adaugă următoarele widget-uri:
   - **Gauge** pentru umiditatea solului (V0).
   - **Gauge** pentru umiditatea aerului (V2).
   - **Gauge** pentru temperatura aerului (V3).
   - **Gauge** pentru luminozitate (V6).
   - **Value Display** pentru nivelul apei (V7).
   - **Button** pentru controlul pompei de apă (V1).
