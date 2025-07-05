/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRLOOPHVAC_SUPPLYPATH_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_SUPPLYPATH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_SupplyPathFields
 *  \brief Enumeration of AirLoopHVAC:SupplyPath's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_SupplyPathFields, )
#else
class AirLoopHVAC_SupplyPathFields: public ::EnumBase<AirLoopHVAC_SupplyPathFields> {
 public: 
  enum domain 
  {
Name, SupplyAirPathInletNodeName,   };
  AirLoopHVAC_SupplyPathFields()
   : EnumBase<AirLoopHVAC_SupplyPathFields>(Name) {} 
  AirLoopHVAC_SupplyPathFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_SupplyPathFields>(t_name) {} 
  AirLoopHVAC_SupplyPathFields(int t_value) 
   : EnumBase<AirLoopHVAC_SupplyPathFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_SupplyPathFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_SupplyPathFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_SupplyPathFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ AirLoopHVAC_SupplyPathFields::Name, "Name", "Name"},
{ AirLoopHVAC_SupplyPathFields::SupplyAirPathInletNodeName, "SupplyAirPathInletNodeName", "Supply Air Path Inlet Node Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_SupplyPathFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_SupplyPathFields> OptionalAirLoopHVAC_SupplyPathFields ;
#endif

/** \class AirLoopHVAC_SupplyPathExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:SupplyPath's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_SupplyPathExtensibleFields, )
#else
class AirLoopHVAC_SupplyPathExtensibleFields: public ::EnumBase<AirLoopHVAC_SupplyPathExtensibleFields> {
 public: 
  enum domain 
  {
ComponentObjectType, ComponentName,   };
  AirLoopHVAC_SupplyPathExtensibleFields()
   : EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>(ComponentObjectType) {} 
  AirLoopHVAC_SupplyPathExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>(t_name) {} 
  AirLoopHVAC_SupplyPathExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_SupplyPathExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_SupplyPathExtensibleFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ AirLoopHVAC_SupplyPathExtensibleFields::ComponentObjectType, "ComponentObjectType", "Component Object Type"},
{ AirLoopHVAC_SupplyPathExtensibleFields::ComponentName, "ComponentName", "Component Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_SupplyPathExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_SupplyPathExtensibleFields> OptionalAirLoopHVAC_SupplyPathExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_SUPPLYPATH_FIELDENUMS_HXX
