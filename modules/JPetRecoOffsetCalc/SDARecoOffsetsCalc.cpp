/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file SDARecoOffsetsCalc.cpp
 */

#include <sstream>
#include <stdlib.h>
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"
#include "SDARecoOffsetsCalc.h"

SDARecoOffsetsCalc::SDARecoOffsetsCalc(const char* name, const char* description) 
: JPetTask(name, description),fCurrentEventNumber(0){}
SDARecoOffsetsCalc::~SDARecoOffsetsCalc(){}
void SDARecoOffsetsCalc::init(const JPetTaskInterface::Options&){
	fBadSignals = 0;
}
void SDARecoOffsetsCalc::exec(){
	if(auto signal = dynamic_cast<const JPetRecoSignal*const>(getEvent())){
		fOffset = JPetRecoSignalTools::calculateOffset(*signal);
		if ( fOffset == JPetRecoSignalTools::ERRORS::badOffset ) {
			WARNING( Form("Problem with calculating fOffset for event: %d", fCurrentEventNumber) );
			JPetRecoSignalTools::saveBadSignalIntoRootFile(*signal, fBadSignals, "badOffsets.root");
			fBadSignals++;
		}else{
			auto signalWithOffset = *signal;
			signalWithOffset.setOffset(fOffset);
			fWriter->write(signalWithOffset);
		}
		fCurrentEventNumber++;
	}
}
void SDARecoOffsetsCalc::terminate()
{
	int fEventNb = fCurrentEventNumber;
	double goodPercent = (fEventNb-fBadSignals) * 100.0/fEventNb;
	INFO(Form("Amount of signals in input file: %d", fEventNb ) );
	INFO(Form("Offset calculation complete \nAmount of bad signals: %d \n %f %% of data is good" , fBadSignals, goodPercent) );
}
void SDARecoOffsetsCalc::setWriter(JPetWriter* writer) {
	fWriter = writer;
}
