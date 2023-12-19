package com.example.ITMOhw3

import com.example.ITMOhw3.user.User
import com.example.ITMOhw3.user.Users
import org.springframework.http.HttpStatus
import org.springframework.http.ResponseEntity
import org.springframework.security.crypto.password.PasswordEncoder
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.PostMapping
import org.springframework.web.bind.annotation.RequestBody
import org.springframework.web.bind.annotation.RestController

@RestController
class RegistrationController(
        private val users: Users,
        private val passwordEncoder: PasswordEncoder
) {
    @PostMapping("/registration")
    fun addUser(@RequestBody user: User): ResponseEntity<*> {
        val userFromDB: User? = users.findByUsername(user.getUsername())
        if (userFromDB != null) {
            println("User exists!")
            println(user)
            return ResponseEntity<Any?>("exists", HttpStatus.CONFLICT)
        }
        if (user.getUsername().trim() == "" || user.getPassword().trim().equals("")) {
            return ResponseEntity<Any?>("null", HttpStatus.BAD_REQUEST) // на всякий случай...
        }
        user.password = passwordEncoder.encode(user.getPassword().trim())
        user.username = user.getUsername().trim()
        users.save(user)

        return ResponseEntity<Any?>(HttpStatus.OK)
    }

    @GetMapping("/users")
    fun points(): ResponseEntity<*> {
        return ResponseEntity<Any?>(users.getUsernames(), HttpStatus.OK)
    }
}
