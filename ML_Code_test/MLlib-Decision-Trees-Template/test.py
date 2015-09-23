import predictionio
engine_client = predictionio.EngineClient(url="http://localhost:8000")
print engine_client.send_query({"features": [0, 0, 0]})
print engine_client.send_query({"features": [0, 0, 1]})
print engine_client.send_query({"features": [0, 1, 0]})
print engine_client.send_query({"features": [0, 1, 1]})
print engine_client.send_query({"features": [0, 0, 2]})
print engine_client.send_query({"features": [0, 2, 0]})
print engine_client.send_query({"features": [0, 2, 2]})
