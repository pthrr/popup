#pragma once

/* struct ScopeGuard; */

/* auto make_guard( std::function< void() >& onExitScope ) -> ScopeGuard */
/* { */
/*     return ScopeGuard( std::move( onExitScope ) ); */
/* } */

/* struct ScopeGuard */
/* { */
/*     explicit ScopeGuard( std::function< void() > onExitScope ) */
/*         : m_onExitScope( std::move( onExitScope ) ) */
/*     { */
/*     } */

/*     ~ScopeGuard() */
/*     { */
/*         if( not m_dismissed and m_onExitScope ) { */
/*             m_onExitScope(); */
/*         } */
/*     } */

/*     ScopeGuard( ScopeGuard const& ) = delete; */
/*     auto operator=( ScopeGuard const& ) -> ScopeGuard& = delete; */

/*     ScopeGuard( ScopeGuard const&& ) = delete; */
/*     auto operator=( ScopeGuard const&& ) -> ScopeGuard&& = delete; */

/*     auto dismiss() -> void */
/*     { */
/*         m_dismissed = true; */
/*     } */

/* private: */
/*     std::function< void() > m_onExitScope; */
/*     bool m_dismissed{ false }; */
/* }; */

namespace helpers {

} // namespace helpers
