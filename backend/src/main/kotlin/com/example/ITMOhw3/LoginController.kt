package com.example.ITMOhw3

import com.example.ITMOhw3.user.User
import com.example.ITMOhw3.user.Users
import org.springframework.http.HttpStatus
import org.springframework.http.ResponseEntity
import org.springframework.security.authentication.AuthenticationManager
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken
import org.springframework.security.core.Authentication
import org.springframework.security.core.AuthenticationException
import org.springframework.security.core.context.SecurityContextHolder
import org.springframework.web.bind.annotation.PostMapping
import org.springframework.web.bind.annotation.RequestBody
import org.springframework.web.bind.annotation.RestController

@RestController
class LoginController(
        private val users: Users,
        private val authenticationManager: AuthenticationManager
) {
    @PostMapping(path = ["/login"])
    fun login(@RequestBody user: User): ResponseEntity<*> {
        return try {
            println(user)
            if (user.getUsername() == "") {
                return ResponseEntity<Any?>(HttpStatus.BAD_REQUEST)
            }
            if (user.getPassword() == "") {
                return ResponseEntity<Any?>(HttpStatus.BAD_REQUEST)
            }
            val authentication: Authentication =
                    authenticationManager.authenticate(
                            UsernamePasswordAuthenticationToken(
                                    user.getUsername(),
                                    user.getPassword()
                            )
                    )
            SecurityContextHolder.getContext().authentication = authentication

            val userFromDB: User? = users.findByUsername(user.getUsername())
            if (userFromDB == null) {
                println("Пользователь не существует")
                return ResponseEntity<Any>(HttpStatus.BAD_REQUEST)
            }

            ResponseEntity<Any>(HttpStatus.OK)
        } catch (ex: AuthenticationException) {
            println(ex.toString())
            println("Попытка авторизации несуществующего пользователя")
            ResponseEntity<Any>(HttpStatus.BAD_REQUEST)
        }
    }
}
