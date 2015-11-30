import predictionio

engine_client = predictionio.EngineClient(url="http://localhost:8000")

print engine_client.send_query({"webaccess": "A", "num": 10})

