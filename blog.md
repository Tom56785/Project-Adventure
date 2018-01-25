---
layout: default
title: 'Blog'
permalink: /blog/
---

# Development Blog


<div class="container">

  <div class="blog-posts">
    {% for post in site.posts %}
      <div class="blog-post spacing">
        <h2><a href="{{ post.url }}">{{ post.title }}</a></h2>
        <p class="summary">
          <span class="date">
            {{ post.date | date: '%B %d, %Y' }}
          </span>
        </p>
        {{ post.excerpt }}
      </div>
    {% endfor %}
  </div>
</div>
