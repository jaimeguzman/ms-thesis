"""
Send sample query to prediction engine
"""

import predictionio
import readline

engine_client = predictionio.EngineClient(url="http://localhost:8000")
while True:
    word = raw_input('Enter a Sequences or a single page to predict the next user webaccess: \n')
    print engine_client.send_query({"webaccess": word, "num": 10})