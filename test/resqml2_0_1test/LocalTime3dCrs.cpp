/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "LocalTime3dCrs.h"
#include "../config.h"
#include "common/EpcDocument.h"
#include "../catch.hpp"

using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace std;

const char* LocalTime3dCrs::defaultUuid = "8f8285a7-f1e7-4964-a9e1-e815c82c65e0";
const char* LocalTime3dCrs::defaultTitle = "Local Time 3d Crs Test";

LocalTime3dCrs::LocalTime3dCrs(const string & epcDocPath)
	: AbstractLocal3dCrsTest(epcDocPath, defaultUuid, defaultTitle)
{
}

LocalTime3dCrs::LocalTime3dCrs(EpcDocument* epcDoc, bool init)
	: AbstractLocal3dCrsTest(epcDoc, defaultUuid, defaultTitle)
{
	if (init)
		this->initEpcDoc();
	else
		this->readEpcDoc();
}

void LocalTime3dCrs::initEpcDocHandler()
{
	epcDoc->createLocalTime3dCrs(uuid, title, 1.0, 0.1, 15, .0, gsoap_resqml2_0_1::eml20__LengthUom__m, 23031, gsoap_resqml2_0_1::eml20__TimeUom__s, gsoap_resqml2_0_1::eml20__LengthUom__m, "Unknown", false);
}

void LocalTime3dCrs::readEpcDocHandler()
{
	REQUIRE( epcDoc->getLocalTime3dCrsSet().size() == 1 );
}

