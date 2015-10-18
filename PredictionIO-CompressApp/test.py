import predictionio
engine_client = predictionio.EngineClient(url="http://localhost:8000")
print engine_client.send_query({"features": [1, 0, 0]})
print engine_client.send_query({"features": [1, 1, 0]})
print engine_client.send_query({"features": [1, 1, 1]})
print engine_client.send_query({"features": [2, 0, 0]})
print engine_client.send_query({"features": [1, 0, 0]})
