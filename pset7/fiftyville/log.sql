SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
-- 10h15 no tribunal da rua. Entrevistas realizadas com 3 testemunhas.

SELECT activity, license_plate FROM courthouse_security_logs WHERE hour = 10 AND minute = 15;
-- exit|11J91FW

SELECT name, transcript FROM interviews WHERE day = 28 AND month = 7;
-- Jose|“Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- Eugene|“I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- Barbara|“You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame. DEPOIS DE UNS 10 MINUTOS, ELE ENTROU NO CARRO NO TRIBUNAL -> OLHAR CÂMERA DE SEGURANÇA
-- Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money. DE MANHÃ, EUGENE ENCONTROU ELE ESTAVA SACANDO DINHEIRO NO CAIXA ELETRÔNICO (ATM) NA RUA FIFER STREET
-- Raymond|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. ANTES DELE SAIR DO TRIBUNAL, ELE ESTAVA CONVERSANDO COM ALGUÉM POR CERCA DE UM MINUTO. PLANEJANDO PEGAR O VOO MAIS CEDO PARA SAIR DE FIFTYVILLE AMANHÃ (29 JULHO). PEDIU PARA A PESSOA DO TELEFONE COMPRAR A PASSAGEM.

SELECT people.name, atm_transactions.account_number FROM atm_transactions
INNER JOIN people ON people.id = bank_accounts.person_id
INNER JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw";
-- TODO MUNDO QUE SACOU NO DIA 28/JUL
-- Danielle|28500762
-- Bobby|28296815
-- Ernest|49610011
-- Russell|26013199

SELECT courthouse_security_logs.hour, courthouse_security_logs.minute, courthouse_security_logs.license_plate, courthouse_security_logs.activity, people.name FROM courthouse_security_logs
INNER JOIN people ON people.license_plate = courthouse_security_logs.license_plate
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 14 AND minute <= 35;
-- DEPOIS DE UNS 10 MINUTOS, ELE ENTROU NO CARRO NO TRIBUNAL -> OLHAR CÂMERA DE SEGURANÇA
-- ENTRADA E SAÍDA DE CARROS DENTRO DO INTERVALO DE 10 MIN (DEPOIS DE 10h15)
-- 10|18|94KL13X|exit|Ernest
-- 10|19|4328GD8|exit|Danielle
-- 10|20|G412CB7|exit|Roger
-- 10|23|322W7JE|exit|Russell
-- 10|23|0NTHK55|exit|Evelyn

-- 10|35|1106N58|exit|Madison

SELECT people_caller.name AS caller_name, people_caller.phone_number, people_receiver.name AS receiver_name, people_receiver.phone_number, phone_calls.duration FROM phone_calls
INNER JOIN people AS people_caller ON people_caller.phone_number = phone_calls.caller
INNER JOIN people AS people_receiver ON people_receiver.phone_number = phone_calls.receiver
WHERE phone_calls.month = 7 AND phone_calls.day = 28
ORDER BY phone_calls.duration ASC;
-- Evelyn|(499) 555-9472|Larry|(892) 555-8872|36
-- Madison|(286) 555-6063|James|(676) 555-6554|43
-- Ernest|(367) 555-5533|Berthold|(375) 555-8161|45
-- Russell|(770) 555-1861|Philip|(725) 555-3243|49
-- Evelyn|(499) 555-9472|Melissa|(717) 555-1342|50
-- Roger|(130) 555-0289|Jack|(996) 555-8899|51
-- Bobby|(826) 555-1652|Doris|(066) 555-9701|55
-- Kathryn|(609) 555-5876|Danielle|(389) 555-5198|60

-- Ernest|(367) 555-5533|Carl|(704) 555-5790|75

SELECT airport_origin.city, airport_origin.id, airport_destiny.city, airport_destiny.id, flights.day, flights.hour, flights.minute, people.name FROM flights
INNER JOIN airports AS airport_origin ON airport_origin.id = flights.origin_airport_id
INNER JOIN airports AS airport_destiny ON airport_destiny.id = flights.destination_airport_id
INNER JOIN passengers ON passengers.flight_id = flights.id
INNER JOIN people ON people.passport_number = passengers.passport_number
WHERE flights.month = 7 AND flights.day = 29 AND flights.origin_airport_id = 8
ORDER BY flights.hour ASC, flights.minute ASC;
-- PRIMEIRO VOO DO DIA: TODOS OS PASSAGEIROS
-- 8|London|4|29|8|20|Doris
-- 8|London|4|29|8|20|Roger
-- 8|London|4|29|8|20|Ernest
-- 8|London|4|29|8|20|Madison
-- 8|London|4|29|8|20|Bobby
-- 8|London|4|29|8|20|Danielle