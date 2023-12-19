package com.example.ITMOhw3

import org.springframework.http.HttpStatus
import org.springframework.http.ResponseEntity
import org.springframework.security.core.context.SecurityContextHolder
import org.springframework.web.bind.annotation.*

@CrossOrigin
@RestController
class CommentController {

    companion object {
        val list1 = mutableListOf<NamedCommentModel>()
        val list2 = mutableListOf<NamedCommentModel>()
        val list3 = mutableListOf<NamedCommentModel>()
    }

    @GetMapping("/getChatIds")
    fun getChatIds(): MutableList<Int> {
        return MutableList(3) { it + 1 }
    }

    @GetMapping("/allComments/1")
    fun allComments1(): MutableList<NamedCommentModel> {
        return list1
    }

    @PostMapping("/addComment/1")
    fun addComment1(@RequestBody comment: CommentModel): ResponseEntity<Any> {
        if (comment.comment.length == 0 || comment.comment.length > 1000) {
            return ResponseEntity(HttpStatus.BAD_REQUEST)
        }
        val username = SecurityContextHolder.getContext().authentication.getName()

        list1.add(NamedCommentModel(username, comment.comment, comment.time))
        return ResponseEntity(HttpStatus.ACCEPTED)
    }

    @GetMapping("/allComments/2")
    fun allComments2(): MutableList<NamedCommentModel> {
        return list2
    }

    @PostMapping("/addComment/2")
    fun addComment2(@RequestBody comment: CommentModel): ResponseEntity<Any> {
        if (comment.comment.length == 0 || comment.comment.length > 1000) {
            return ResponseEntity(HttpStatus.BAD_REQUEST)
        }
        val username = SecurityContextHolder.getContext().authentication.getName()

        list2.add(NamedCommentModel(username, comment.comment, comment.time))
        return ResponseEntity(HttpStatus.ACCEPTED)
    }

    @GetMapping("/allComments/3")
    fun allComments3(): MutableList<NamedCommentModel> {
        return list3
    }

    @PostMapping("/addComment/3")
    fun addComment3(@RequestBody comment: CommentModel): ResponseEntity<Any> {
        if (comment.comment.length == 0 || comment.comment.length > 1000) {
            return ResponseEntity(HttpStatus.BAD_REQUEST)
        }
        val username = SecurityContextHolder.getContext().authentication.getName()

        list3.add(NamedCommentModel(username, comment.comment, comment.time))
        return ResponseEntity(HttpStatus.ACCEPTED)
    }
}
