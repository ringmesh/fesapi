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
#include "resqml2_0_1/WellboreFeature.h"

#include <stdexcept>

#include "witsml1_4_1_1/Well.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* WellboreFeature::XML_TAG = "WellboreFeature";

WellboreFeature::WellboreFeature(soap* soapContext, const string & guid, const std::string & title) :witsmlWellbore(nullptr)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREWellboreFeature(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void WellboreFeature::setWitsmlWellbore(WITSML1_4_1_1_NS::Wellbore * wellbore)
{
	witsmlWellbore = wellbore;
	wellbore->resqmlWellboreFeature = this;

	if (updateXml)
	{
		resqml2__obj_USCOREWellboreFeature* resqmlWellbore = static_cast<resqml2__obj_USCOREWellboreFeature*>(gsoapProxy2_0_1);
		resqmlWellbore->WitsmlWellbore = soap_new_resqml2__WitsmlWellboreReference(gsoapProxy2_0_1->soap, 1);
		resqmlWellbore->WitsmlWellbore->WitsmlWellbore = wellbore->newResqmlReference();
		resqmlWellbore->WitsmlWellbore->WitsmlWell = wellbore->getWell()->newResqmlReference();
	}
}

vector<Relationship> WellboreFeature::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractTechnicalFeature::getAllEpcRelationships();

	if (witsmlWellbore)
	{
		Relationship relWellbores(witsmlWellbore->getPartNameInEpcDocument(), "", witsmlWellbore->getUuid());
		relWellbores.setDestinationObjectType();
		result.push_back(relWellbores);

		Relationship relWells(witsmlWellbore->getWell()->getPartNameInEpcDocument(), "", witsmlWellbore->getWell()->getUuid());
		relWells.setDestinationObjectType();
		result.push_back(relWells);
	}

	return result;
}

void WellboreFeature::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	resqml2__obj_USCOREWellboreFeature* resqmlWellbore = static_cast<resqml2__obj_USCOREWellboreFeature*>(gsoapProxy2_0_1);

	if (resqmlWellbore->WitsmlWellbore && resqmlWellbore->WitsmlWellbore->WitsmlWellbore)
	{
		WITSML1_4_1_1_NS::Wellbore* tmp = static_cast<WITSML1_4_1_1_NS::Wellbore*>(epcDoc->getWitsmlAbstractObjectByUuid(resqmlWellbore->WitsmlWellbore->WitsmlWellbore->UUID));
		if (tmp)
		{
			updateXml = false;
			setWitsmlWellbore(tmp);
			updateXml = true;
		}
	}
}

