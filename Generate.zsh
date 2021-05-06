#! /bin/zsh

source Setup.sh

bin/gen 1  5020 50 10000 0 rootFiles/NoBoost/gen_job1.root > outputs/NoBoost_gen_job1.out 2> errors/NoBoost_gen_job1.err &
bin/gen 2  5020 50 10000 0 rootFiles/NoBoost/gen_job2.root > outputs/NoBoost_gen_job2.out 2> errors/NoBoost_gen_job2.err &
bin/gen 3  5020 50 10000 0 rootFiles/NoBoost/gen_job3.root > outputs/NoBoost_gen_job3.out 2> errors/NoBoost_gen_job3.err &
bin/gen 4  5020 50 10000 0 rootFiles/NoBoost/gen_job4.root > outputs/NoBoost_gen_job4.out 2> errors/NoBoost_gen_job4.err &

wait

bin/gen 5  5020 50 10000 0 rootFiles/NoBoost/gen_job5.root > outputs/NoBoost_gen_job5.out 2> errors/NoBoost_gen_job5.err &
bin/gen 6  5020 50 10000 0 rootFiles/NoBoost/gen_job6.root > outputs/NoBoost_gen_job6.out 2> errors/NoBoost_gen_job6.err &
bin/gen 7  5020 50 10000 0 rootFiles/NoBoost/gen_job7.root > outputs/NoBoost_gen_job7.out 2> errors/NoBoost_gen_job7.err &
bin/gen 8  5020 50 10000 0 rootFiles/NoBoost/gen_job8.root > outputs/NoBoost_gen_job8.out 2> errors/NoBoost_gen_job8.err &

wait

bin/gen 11 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job11.root > outputs/Boost_0p465_gen_job11.out 2> errors/Boost_0p465_gen_job11.err &
bin/gen 12 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job12.root > outputs/Boost_0p465_gen_job12.out 2> errors/Boost_0p465_gen_job12.err &
bin/gen 13 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job13.root > outputs/Boost_0p465_gen_job13.out 2> errors/Boost_0p465_gen_job13.err &
bin/gen 14 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job14.root > outputs/Boost_0p465_gen_job14.out 2> errors/Boost_0p465_gen_job14.err &

wait

bin/gen 15 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job15.root > outputs/Boost_0p465_gen_job15.out 2> errors/Boost_0p465_gen_job15.err &
bin/gen 16 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job16.root > outputs/Boost_0p465_gen_job16.out 2> errors/Boost_0p465_gen_job16.err &
bin/gen 17 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job17.root > outputs/Boost_0p465_gen_job17.out 2> errors/Boost_0p465_gen_job17.err &
bin/gen 18 5020 50 10000 0.465 rootFiles/Boost_0p465/gen_job18.root > outputs/Boost_0p465_gen_job18.out 2> errors/Boost_0p465_gen_job18.err &

wait

hadd -f rootFiles/NoBoost/gen_all.root rootFiles/NoBoost/gen_job*.root
hadd -f rootFiles/Boost_0p465/gen_all.root rootFiles/Boost_0p465/gen_job*.root
rm rootFiles/NoBoost/gen_job*.root
rm rootFiles/Boost_0p465/gen_job*.root
