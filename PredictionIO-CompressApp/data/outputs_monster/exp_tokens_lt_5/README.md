
## To Run this Experiment yoi mus to first of all


run 

pio-start-all
pio eventserver


check if everything is working


pio status

Create the apps for store the data

```
    pio app new exp_tokens_lt_5_10 &
    pio app new exp_tokens_lt_5_100 &
    pio app new exp_tokens_lt_5_1000 &
    pio app new exp_tokens_lt_5_10000 &
    pio app new exp_tokens_lt_5_100000 &
    pio app new exp_okens_lt_5_1000000 &
```




later you have to import all the event (Data)


[INFO] [App$]   exp_tokens_lt_5_10 		|   37 | oRrJVihAuSnfbHoSHaYXw82UsuHdsAS7lapKxuPUniQPbUsRPZP5RUUt2GIAvEqq | (all)
[INFO] [App$]  exp_tokens_lt_5_100 		|   38 | 2zm3f7WwoRGRSCW5dkRTSOWnfWQj6y8DyfHix2JMljqAw9RA1v8QFxTXuVhhW1vN | (all)
[INFO] [App$] exp_tokens_lt_5_1000 		|   39 | WVnt7yctlGU7o0wVCNcPFTdRwLsHfrrjdwqQNcHSZue76DZmE29cWtO0fTrkXnPy | (all)
[INFO] [App$] exp_tokens_lt_5_10000 	|   40 | OJscS3XefZjeg37SWbVrRZL7PbznX7tmye6m7jfkOODtc7lV9R9a4ti6AkjrT8Ch | (all)
[INFO] [App$] exp_tokens_lt_5_100000 	|   41 | vKSrB3n8p1RFazTTko6YODoPT0bzMTfPLTheYWpKSCdZOiKXyAClqMMQjb4nNake | (all)
[INFO] [App$] exp_tokens_lt_5_1000000 	|   42 | PCN7NE0rNAnOats9VisB1nTxP2nA0TPyVzQ7zGImiVH1L5dIq9j894Jg2Ooyx4W6 | (all)



python data/import_eventserver.py --file data/exp_tokens_lt_5_10.seq --access_key oRrJVihAuSnfbHoSHaYXw82UsuHdsAS7lapKxuPUniQPbUsRPZP5RUUt2GIAvEqq
python data/import_eventserver.py --file data/exp_tokens_lt_5_100.seq --access_key 2zm3f7WwoRGRSCW5dkRTSOWnfWQj6y8DyfHix2JMljqAw9RA1v8QFxTXuVhhW1vN
python data/import_eventserver.py --file data/exp_tokens_lt_5_1000.seq --access_key WVnt7yctlGU7o0wVCNcPFTdRwLsHfrrjdwqQNcHSZue76DZmE29cWtO0fTrkXnPy




#exp_tokens_lt_5_100

	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_90t_10e.out

	real    0m56.760s
	user    1m47.774s
	sys     0m9.005s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$

	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_80t_20e.out

	real    0m55.075s
	user    1m49.343s
	sys     0m8.603s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_70t_30e.out

	real    0m52.360s
	user    1m41.651s
	sys     0m8.091s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_60t_40e.out

	real    0m51.424s
	user    1m35.605s
	sys     0m7.560s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_50t_50e.out

	real    0m49.017s
	user    1m31.948s
	sys     0m7.323s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_40t_60e.out

	real    0m47.408s
	user    1m35.683s
	sys     0m6.441s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_30t_70e.out

	real    0m45.532s
	user    1m27.578s
	sys     0m6.332s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$




	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_20t_80e.out

	real    0m44.239s
	user    1m25.498s
	sys     0m5.903s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_100_10t_90e.out

	real    0m42.729s
	user    1m18.305s
	sys     0m5.524s
	ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$
------------------- #exp_tokens_lt_5_100----------------------




#exp_tokens_lt_5_1000


------------------- #exp_tokens_lt_5_1000 ----------------------

ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_1000_900t_100e.out

real    13m16.117s
user    24m15.471s
sys     2m28.512s
ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$





ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_1000_500t_500e.out

real    5m8.468s
user    10m13.336s
sys     1m3.673s
ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$



ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_1000_250t_750e.out

real    2m4.091s
user    4m39.219s
sys     0m34.429s
ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$


ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$ time sh eval.sh > data/outputs_monster/exp_tokens_lt_5/exp_tokens_lt_5_1000_100t_900e.out

real    1m3.146s
user    2m33.488s
sys     0m13.419s
ubuntu@ip-172-31-3-226:~/PredictionIO-CompressApp$




