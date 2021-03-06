#ifndef __ALADDIN_CORE_CORE_MARCOS_H__
#define __ALADDIN_CORE_CORE_MARCOS_H__

/*
 * Created by phuctm97 on Sep 27th 2017
 */

// Common Methods
#ifndef M_PI
#define M_PI      3.14159265358
#endif

#ifndef MIN
#define MIN( x, y ) (((x) > (y)) ? (y) : (x))
#endif

#ifndef MAX
#define MAX( x, y ) (((x) < (y)) ? (y) : (x))
#endif

#undef min
#undef max

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

#ifdef ALA_ASSERT
#undef ALA_ASSERT
#endif
#define ALA_ASSERT( _expr_ ) assert( _expr_ )

#define SAFE_DELETE(_ptr_) \
  if(_ptr_ != NULL) { \
    delete _ptr_; \
    _ptr_ = NULL; \
  }

// Aladdin Defines
#define NAMESPACE_ALA         namespace ala
#define USING_NAMESPACE_ALA   using namespace ala

// ClassMeta
#define ALA_DECLARE_CLASS_META \
  static ClassMeta CLASS_META; \
  virtual const ClassMeta &getClassMeta() const { return CLASS_META; }


#define ALA_DEFINE_CLASS_META_0( _class_, _classname_ ) ala::ClassMeta _class_::CLASS_META( _classname_ );

#define ALA_DEFINE_CLASS_META_1( _class_, _classname_, _baseclass1_ ) \
ala::ClassMeta _class_::CLASS_META( \
  _classname_, \
  &_baseclass1_::CLASS_META );

#define ALA_DEFINE_CLASS_META_2( _class_, _classname_, _baseclass1_, _baseclass2_ ) \
ala::ClassMeta _class_::CLASS_META( \
  _classname_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META );

#define ALA_DEFINE_CLASS_META_3( _class_, _classname_, _baseclass1_, _baseclass2_, _baseclass3_ ) \
ala::ClassMeta _class_::CLASS_META( \
  _classname_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META, \
  &_baseclass3_::CLASS_META );

#define ALA_DEFINE_CLASS_META_4( _class_, _classname_, _baseclass1_, _baseclass2_, _baseclass3_, _baseclass4_ ) \
ala::ClassMeta _class_::CLASS_META( \
  _classname_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META, \
  &_baseclass3_::CLASS_META, \
  &_baseclass4_::CLASS_META );

#define ALA_DEFINE_CLASS_META_5( _class_, _classname_, _baseclass1_, _baseclass2_, _baseclass3_, _baseclass4_, _baseclass5_ ) \
ala::ClassMeta _class_::CLASS_META( \
  _classname_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META, \
  &_baseclass3_::CLASS_META, \
  &_baseclass4_::CLASS_META, \
  &_baseclass5_::CLASS_META );

#define ALA_CLASS_HEADER_0( _class_ ) \
  class _class_ : public ala::Base { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_1( _class_, _base1_ ) \
  class _class_ : public _base1_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_2( _class_, _base1_, _base2_ ) \
  class _class_ : public _base1_, public _base2_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_3( _class_, _base1_, _base2_, _base3_ ) \
  class _class_ : public _base1_, public _base2_, public _base3_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_4( _class_, _base1_, _base2_, _base3_, _base4_ ) \
  class _class_ : public _base1_, public _base2_, public _base3_, public _base4_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_5( _class_, _base1_, _base2_, _base3_, _base4_, _base5_ ) \
  class _class_ : public _base1_, public _base2_, public _base3_, public _base4_, public _base5_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_SOURCE_0( _class_, _classname_ ) \
ALA_DEFINE_CLASS_META_1(_class_, _classname_, ala::Base)

#define ALA_CLASS_SOURCE_1( _class_, _classname_, _base1_ ) \
ALA_DEFINE_CLASS_META_1(_class_, _classname_, _base1_)

#define ALA_CLASS_SOURCE_2( _class_, _classname_, _base1_, _base2_ ) \
ALA_DEFINE_CLASS_META_2(_class_, _classname_, _base1_, _base2_)

#define ALA_CLASS_SOURCE_3( _class_, _classname_, _base1_, _base2_, _base3_ ) \
ALA_DEFINE_CLASS_META_3(_class_, _classname_, _base1_, _base2_, _base3_ )

#define ALA_CLASS_SOURCE_4( _class_, _classname_, _base1_, _base2_, _base3_, _base4_ ) \
ALA_DEFINE_CLASS_META_4(_class_, _classname_, _base1_, _base2_, _base3_, _base4_ )

#define ALA_CLASS_SOURCE_5( _class_, _classname_, _base1_, _base2_, _base3_, _base4_, _base5_ ) \
ALA_DEFINE_CLASS_META_5(_class_, _classname_, _base1_, _base2_, _base3_, _base4_, _base5_ )

#endif //!__ALADDIN_CORE_CORE_MARCOS_H__
