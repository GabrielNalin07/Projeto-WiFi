#include <Arduino.h>
#include <WiFi.h>
#include <ezTime.h>

void conexaoWifi();
void reConexaoWifi();

const char *SSID = "SENAI EDUCACIONAL";
const char *SENHA = "info@134";
int DiasRestantesAno();

Timezone sp;

const unsigned long tempoConexao = 10000;
const unsigned long tempoReconexao = 5000;

String diaSemanaBR()
{

  const char *dias[] = {
      "Domingo", "Segunda-feira", "Terca-feira",
      "Quarta-feira", "Quinta-feira", "Sexta-feira",
      "Sabado"};

  return dias[sp.weekday() - 1];
}

String mesBR()
{
  const char *meses[] = {
      "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
  return meses[sp.month() - 1];
}

void setup()
{
  Serial.begin(115200);

  conexaoWifi();
  if (WiFi.status() == WL_CONNECTED)
  {

    sp.setLocation("America/Sao_Paulo");

    waitForSync();
    Serial.printf("Hoje e %s de %s de %s, %s e faltam %i dias para o ano novo. \n ", String(sp.day()).c_str(), mesBR().c_str(), sp.dateTime("Y").c_str(), diaSemanaBR().c_str(), DiasRestantesAno());
  }


  }

  // conexão wifi
  void conexaoWifi()
  {
    Serial.printf(" Conectando ao Wifi: %s\n", SSID);

    WiFi.begin(SSID, SENHA);

    unsigned long tempof1 = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - tempof1 < tempoConexao)
    {
      Serial.print(".");
      delay(500);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("\nWifi conectado com sucesso");
      Serial.print("Endereco IP: ");
      Serial.println(WiFi.localIP());
    }
    else
    {
      Serial.println("\nFalha ao conectar");
    }
  }

  // Reconexao
  void reConexaoWifi()
  {

    unsigned long tempoAtual = millis();
    static unsigned long tempoUltimaConexao = 0;

    if (tempoAtual - tempoUltimaConexao >= tempoReconexao)
      ;
    {
      if (WiFi.status() != WL_CONNECTED)
      {
        Serial.println("Conexao Wifi perdida");
        conexaoWifi();
      }
      tempoUltimaConexao = millis();
    }
  }

  void loop()
  {
  }

  int DiasRestantesAno()
  {

    int TotalDias = 365;

    return TotalDias - sp.dayOfYear();
  }

