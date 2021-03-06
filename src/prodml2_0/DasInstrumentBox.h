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
#pragma once

#include "prodml2_0/DasAcquisition.h"

namespace PRODML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT DasInstrumentBox : public PRODML2_0_NS::AbstractObject
	{
	public:
		/**
		* Default constructor
		*/
		DasInstrumentBox() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap		A gsoap context wihch will manage the memory and the serialization/deserialization of this instance.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		DasInstrumentBox(soap* soapContext, const std::string & guid, const std::string & title,
			const std::string & firmwareVersion, const std::string & instrumentName);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DasInstrumentBox(gsoap_eml2_1::_prodml2__DasInstrumentBox* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~DasInstrumentBox() {}
		
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc) {}

		// XML backwards relationships
		std::vector<class DasAcquisition*> dasAcquisitionSet;

		friend void DasAcquisition::setDasInstrumentBox(DasInstrumentBox* dasInstrumentBox);
	};
}

