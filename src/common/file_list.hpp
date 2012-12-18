#pragma once

#include <pni/utils/Types.hpp>
#include <list>
#include "file.hpp"
#include <boost/tokenizer.hpp>

using namespace pni::utils;


    /*!
    \brief an iterable list of files

    This is an iterable list of valid regular files. During list creation all
    files are checked for their existance and validity. This should avoid that a
    program stops after a maybe long time of operation due to a simple file
    error.
    */
    class file_list
    {
        private:
            //! list with files
            std::list<file> _file_list; 

            //some private type definitions
            //! separator type for numeric ranges
            typedef boost::char_separator<char> nrseparator;
            //! tokenizer type for numeric ranges
            typedef boost::tokenizer<nrseparator> nrtokenizer;

            /*!
            \brief file file list from numeric range

            Fill the file list from a numeric range stored in po. 
            
            \param po path string
            */
            bool _fill_from_num_range(const String &po);
        
        public:
            //==================public types====================================
            typedef file value_type;
            typedef std::list<file>::iterator iterator;
            typedef std::list<file>::const_iterator const_iterator;

            //==================constructors and destructor=====================
            //! default constructor
            file_list():_file_list() {}

            //------------------------------------------------------------------
            /*! 
            \brief constructor
            
            Construct obejct from a list of paths. The paths are passed in an
            arbitary container type.
            \tparam CTYPE container type
            \param pl path list
            */
            template<typename CTYPE> file_list(const CTYPE &pl):
                _file_list()
            {
                for(auto po: pl)
                {
                    if(!_fill_from_num_range(po))
                        _file_list.push_back(po);
                }
            }

            //================query methods=====================================
            //! get number of files
            size_t size() const { return _file_list.size(); }

            //=============iterator related methods=============================
            //! get non-const iterator to first element
            iterator begin() { return _file_list.begin(); }

            //------------------------------------------------------------------
            //! get non-const iterator to last+1 delement
            iterator end() { return _file_list.end(); }

            //------------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return _file_list.begin(); }

            //------------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const { return _file_list.end(); }
            

    };