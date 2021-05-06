#! /bin/zsh

source Setup.sh

bin/analyze NoCut rootFiles/NoBoost/gen_all.root rootFiles/NoBoost/hists_NoCut.root &
bin/analyze M0_Cut rootFiles/NoBoost/gen_all.root rootFiles/NoBoost/hists_M0_Cut.root &
bin/analyze MPi_Cut rootFiles/NoBoost/gen_all.root rootFiles/NoBoost/hists_MPi_Cut.root &
bin/analyze MPro_Cut rootFiles/NoBoost/gen_all.root rootFiles/NoBoost/hists_MPro_Cut.root &

bin/analyze boost_NoCut rootFiles/Boost_0p465/gen_all.root rootFiles/Boost_0p465/hists_NoCut.root &
bin/analyze boost_M0_Cut rootFiles/Boost_0p465/gen_all.root rootFiles/Boost_0p465/hists_M0_Cut.root &
bin/analyze boost_MPi_Cut rootFiles/Boost_0p465/gen_all.root rootFiles/Boost_0p465/hists_MPi_Cut.root &
bin/analyze boost_MPro_Cut rootFiles/Boost_0p465/gen_all.root rootFiles/Boost_0p465/hists_MPro_Cut.root &

wait
