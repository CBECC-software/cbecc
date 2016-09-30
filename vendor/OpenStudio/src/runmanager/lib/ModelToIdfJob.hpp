/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.  
*  All rights reserved.
*  
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef RUNMANAGER_LIB_MODELTOIDFJOB_HPP
#define RUNMANAGER_LIB_MODELTOIDFJOB_HPP

#include <boost/filesystem.hpp>
#include <string>
#include "../../utilities/core/Logger.hpp"
#include "Job_Impl.hpp"
#include "JobParam.hpp"
#include "../../utilities/core/Checksum.hpp"

#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDateTime>

namespace openstudio {
  namespace model {
    class Model;
  }

namespace runmanager {
namespace detail {

  /**
   * Job type that converts a Model file into an IDF in process.
   */
  class ModelToIdfJob : public Job_Impl
  {
    Q_OBJECT;

    public:
      /// ModelToIdf constructor. 
      ModelToIdfJob(const UUID &t_uuid,
          const Tools &tools,
          const JobParams &params,
          const Files &files,
      const JobState &t_restoreData);

      virtual ~ModelToIdfJob();

      // Reimplemented virtual functions from Job_Impl
      virtual bool outOfDateImpl(const boost::optional<QDateTime> &t_lastrun) const override;
      virtual std::string description() const override;
      virtual Files outputFilesImpl() const override;
      virtual std::string getOutput() const override;
      virtual void cleanup() override;

      virtual void requestStop() override;

    protected:
      virtual void startImpl(const std::shared_ptr<ProcessCreator> &t_creator) override;

      virtual void basePathChanged() override;

      virtual void standardCleanImpl() override { /* nothing to do for this job type */ }

    private:
      REGISTER_LOGGER("openstudio.runmanager.ModelToIdf");

      void outputFilesImpl_Internal(openstudio::model::Model &t_model);


      FileInfo modelFile() const;

      std::string checksum(const QUrl &t_url) const
      {
        if (t_url.scheme() == "file")
        {
          return openstudio::checksum(toPath(t_url.toLocalFile()));
        } else {
          LOG(Info, "Checksumming unsupported url scheme " << toString(t_url.scheme()) << " just using url name instead of actual file data");
          return openstudio::checksum(toString(t_url.toLocalFile()));
        }

      }

      template<typename T>
        std::string checksum(const T &t) const
        {
          return openstudio::checksum(t);
        }

      mutable QReadWriteLock m_mutex;

      std::map<openstudio::path, FileTrack> m_files; //< Files tracked for outOfDate status
      boost::optional<FileInfo> m_model; //< Model that is being converted
      boost::optional<QDateTime> m_lastrun; //< time of last job run
      mutable boost::optional<Files> m_outputfiles; //< IDF file that was created from run

      std::string m_description; //< Description of job
  }; 

}
}
}
#endif // RUNMANAGER_LIB_MODELTOIDFJOB_HPP
