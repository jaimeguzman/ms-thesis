"""
Import sample data for classification engine
"""

import predictionio
import argparse

# def import_events(client, file):
def import_events(client, file):
  f = open(file, 'r')
  count = 0
  print "Importando la DATA..."
  for line in f:
    data = line.rstrip('\r\n').split(" ")
    # data.remove('')

    # print data
    cliente = client  
    pos = 0
    for features in data:
      # print "El usuario %d vio la pagina %s por %d vez " % (count,features, pos)
      for ft in features:
        pos += 1
        print "entity_id:    %d \t  <feature, pos> == <%s,%d>" % (count,ft,pos )
        cliente.create_event(
          event="view",   #el usuario siempre ve una seccion de PRISA
          entity_type="user",
          entity_id=str(count), # use the count num as user ID
          properties= {
            "page" : ft,
            "pos" :  int(pos)
          }
        )

    count += 1
  f.close()
  print "%s events are imported." % count





if __name__ == '__main__':
  parser = argparse.ArgumentParser(   description="Import sample data for classification engine")
  parser.add_argument('--access_key', default='invald_access_key')
  parser.add_argument('--url',        default="http://localhost:7070")
  parser.add_argument('--file',       default="./data/msnbc990928-10entry.seq")

  args = parser.parse_args()
  print args

  client = predictionio.EventClient(
    access_key=args.access_key,
    url=args.url,
    threads=5,
    qsize=500)

  import_events(client, args.file)
