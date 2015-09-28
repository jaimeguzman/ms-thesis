"""
Import sample data for classification engine
"""

import predictionio
import argparse

def import_events(client, file):
  f = open(file, 'r')
  count = 0
  print "Importing data..."
  for line in f:
    data = line.rstrip('\r\n').split(",")
    plan = data[0]
    attr = data[1].split(" ")
    client.create_event(
      event="$set",
      entity_type="user",
      entity_id=str(count), # use the count num as user ID
      properties= { #represento las vistias como los estados de la cadena de Markov
        "v0" : int(attr[0]),
        "v1" : int(attr[1]),
        "v3" : int(attr[2]),
        "v4" : int(attr[3]),
        "v4" : int(attr[4]),
        "v4" : int(attr[5]),
        "v4" : int(attr[6]),
        "v4" : int(attr[7]),
        "v4" : int(attr[8]),
        "v4" : int(attr[9]),
        "v4" : int(attr[10]),
        "v4" : int(attr[11]),
        "v4" : int(attr[12]),
        "v4" : int(attr[13]),
        "v4" : int(attr[14]),
        "v4" : int(attr[15]),
      }
    )
    count += 1
  f.close()
  print "%s LOS EVENTOS HAN SIDO IMPORTADOS." % count

if __name__ == '__main__':
  parser = argparse.ArgumentParser(
    description="Import sample data for classification engine")
  parser.add_argument('--access_key', default='invald_access_key')
  parser.add_argument('--url', default="http://localhost:7070")
  parser.add_argument('--file', default="./data/sample_decision_trees.txt")

  args = parser.parse_args()
  print args

  client = predictionio.EventClient(
    access_key=args.access_key,
    url=args.url,
    threads=5,
    qsize=500)
  import_events(client, args.file)
